#include <iostream>
#include "Linux_OS_ThreadPool.h"
using namespace std;

void *my_task (void *arg)
{
    printf ("threadid is 0x%x, working on task %d\n", pthread_self(),*(int *) arg);
    sleep (3);              //休息3秒，延长任务的执行时间
    return NULL;
}

int main (int argc, char **argv)
{
    pool_init(3);           //线程池中最多三个活动线程

    int job_num = 5;
    // 每隔一定时间, 向池中投入任务, 一共 5 个任务
    int *jobs = (int *) malloc (sizeof (int) * job_num);
    int i;
    for (i = 0; i < job_num; i++)
    {
        jobs[i] = i;
        sleep(i);
        pool_add_worker(my_task, &jobs[i]);
    }
    // 等待所有任务完成
    sleep(10);
    // 销毁线程池
    pool_destroy();
    free(jobs);
    return 0;
}
