#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <assert.h>


// 线程池里所有运行和等待的任务都是一个CThread_worker, 由于所有任务都在链表里，所以是一个链表结构
typedef struct worker
{

    void *(*process) (void *arg);   // 回调函数，任务运行时会调用此函数，注意也可声明成其它形式
    void *arg;                      // 回调函数的参数
    struct worker *next;
} CThread_worker;

// 线程池结构
typedef struct
{
    pthread_mutex_t queue_lock;
    pthread_cond_t queue_ready;
    CThread_worker *queue_head;   // 链表结构，线程池中所有等待任务
    bool shutdown;                // 是否销毁线程池
    pthread_t *threadid;          // 维持线程链表
    int max_thread_num;           // 线程池中允许的活动线程数目
    int cur_queue_size;           // 当前等待队列的任务数目
} CThread_pool;

int pool_add_worker (void *(*process) (void *arg), void *arg);
void *thread_routine (void *arg);
static CThread_pool *pool = NULL;

void pool_init (int max_thread_num)
{
    pool = (CThread_pool *) malloc (sizeof (CThread_pool));
    pthread_mutex_init (&(pool->queue_lock), NULL);
    pthread_cond_init (&(pool->queue_ready), NULL);
    pool->queue_head = NULL;
    pool->max_thread_num = max_thread_num;
    pool->cur_queue_size = 0;
    pool->shutdown = false;
    pool->threadid =
            (pthread_t *) malloc (max_thread_num * sizeof (pthread_t));
    int i = 0;
    for (i = 0; i < max_thread_num; i++)
    {
        pthread_create (&(pool->threadid[i]), NULL, thread_routine,
                        NULL);
    }
}

//向线程池中加入任务
int pool_add_worker (void *(*process) (void *arg), void *arg)
{
    // 构造一个新任务
    CThread_worker *new_worker =
            (CThread_worker *) malloc (sizeof (CThread_worker));
    new_worker->process = process;
    new_worker->arg = arg;
    new_worker->next = NULL;        // new_worker 为最后一个任务
    pthread_mutex_lock (&(pool->queue_lock));

    // 将任务加入到等待队列中
    CThread_worker *member = pool->queue_head;
    if (member != NULL)
    {
        while (member->next != NULL)
            member = member->next;
        member->next = new_worker;
    }
    else
    {
        pool->queue_head = new_worker;
    }
    assert (pool->queue_head != NULL);
    pool->cur_queue_size++;
    pthread_mutex_unlock (&(pool->queue_lock));
    // 等待队列中有任务了，唤醒一个等待线程.  注意如果所有线程都在忙碌，这句没有任何作用
    pthread_cond_signal(&(pool->queue_ready));
    return 0;
}

/*销毁线程池，等待队列中的任务不会再被执行，但是正在运行的线程会一直
把任务运行完后再退出*/
int pool_destroy ()
{
    if (pool->shutdown)
        return -1;          // 防止两次调用
    pool->shutdown = true;
    pthread_cond_broadcast (&(pool->queue_ready));   // 唤醒所有等待线程，线程池要销毁了
    // 阻塞等待线程退出，否则就成僵尸了
    int i;
    for (i = 0; i < pool->max_thread_num; i++)
        pthread_join (pool->threadid[i], NULL);
    free (pool->threadid);

    // 销毁等待任务队列
    CThread_worker *head = NULL;
    while (pool->queue_head != NULL)
    {
        head = pool->queue_head;
        pool->queue_head = pool->queue_head->next;
        free (head);
    }
    // 销毁条件变量和互斥量
    pthread_mutex_destroy(&(pool->queue_lock));
    pthread_cond_destroy(&(pool->queue_ready));

    free (pool);
    // 销毁后指针置空
    pool=NULL;
    return 0;
}

void *thread_routine (void *arg)
{
    printf ("starting thread 0x%x\n", pthread_self());
    while (1)
    {
        pthread_mutex_lock(&(pool->queue_lock));
        /*
         * 如果等待队列为0并且不销毁线程池，则处于阻塞状态;
         * 注意pthread_cond_wait是一个原子操作，等待前会解锁，唤醒后会加锁
         */
        while (pool->cur_queue_size == 0 && !pool->shutdown)
        {
            printf ("thread 0x%x is waiting\n", pthread_self ());
            pthread_cond_wait(&(pool->queue_ready), &(pool->queue_lock));
        }
        // 将要销毁线程池
        if (pool->shutdown)
        {
            // 遇到break,continue,return等跳转语句，千万不要忘记先解锁
            pthread_mutex_unlock(&(pool->queue_lock));
            printf ("thread 0x%x is exiting\n", pthread_self());
            pthread_exit(NULL);
        }
        printf ("thread 0x%x is starting to work\n", pthread_self());
        // assert是调试的好帮手
        assert (pool->cur_queue_size != 0);
        assert (pool->queue_head != NULL);

        /*等待队列长度减去1，并取出链表中的头元素*/
        pool->cur_queue_size--;
        CThread_worker *worker = pool->queue_head;
        pool->queue_head = worker->next;
        pthread_mutex_unlock (&(pool->queue_lock));
        // 调用回调函数，执行任务
        (*(worker->process)) (worker->arg);
        free (worker);
        worker = NULL;
    }
}

#endif
