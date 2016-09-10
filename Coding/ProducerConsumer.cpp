/*
 * @Author: xuezaigds@gmail.com
 * @Last Modified time: 2016-09-10 11:12:19
 * Worked on Mac OS X
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <dispatch/dispatch.h>          // OS X

const int BufLen = 10;                  // 缓冲区长度
int buf[BufLen] = {0};
int head = 0, tail = 0;                 // 缓存区，首尾指针
int product_NO = 1;                     // 产品序号
const int MProducer=4, NConsumer=1;     // 生产者, 消费者数目

dispatch_semaphore_t empty = dispatch_semaphore_create(BufLen);
dispatch_semaphore_t full = dispatch_semaphore_create(0);
dispatch_semaphore_t mutex = dispatch_semaphore_create(1);

// 将产品放入缓冲区中
void insert_item(int item){
    printf("+++ Create a product: %d \t", item);
    buf[tail] = item;
    tail = (tail+1) % BufLen;
}

// 从缓冲区中取出产品
void remove_item(){
    printf("--- Delete a product: %d \t", buf[head]);
    buf[head] = 0;                     // 消费
    head = (head+1) % BufLen;
}

void print_items(){
    int i=head;
    printf("Current Buf looks like: ");
    int count = 0;
    while (buf[i]!=0){
        printf("%d, ", buf[i]);
        // 缓冲区满,跳出循环
        if(++count == BufLen){
            break;
        }
        i = (i+1)%BufLen;
    }
    printf("\n");
}

void *producerFunc(void *arg)           // 生产者线程
{
    int item;
    while(true)
    {
        dispatch_semaphore_wait(empty, DISPATCH_TIME_FOREVER);
        dispatch_semaphore_wait(mutex, DISPATCH_TIME_FOREVER);
        item = product_NO++;
        insert_item(item);
        print_items();
        dispatch_semaphore_signal(mutex);
        dispatch_semaphore_signal(full);
        sleep(3);
    }
}

void *consumerFunc(void * arg)          // 消费者线程
{
    while(true)
    {
        dispatch_semaphore_wait(full, DISPATCH_TIME_FOREVER);
        dispatch_semaphore_wait(mutex, DISPATCH_TIME_FOREVER);
        remove_item();
        print_items();
        dispatch_semaphore_signal(mutex);
        dispatch_semaphore_signal(empty);
        sleep(5);
    }
}

int main()
{
    pthread_t producer[MProducer];
    for (int i = 0; i < MProducer; ++i)
        if (pthread_create(&producer[i], NULL, producerFunc, NULL) != 0)
        {
            printf("Creating producer %d error.\n", i);
            exit(1);
        }

    pthread_t consumer[NConsumer];
    for (int i = 0; i < NConsumer; ++i)
        if (pthread_create(&consumer[i], NULL, consumerFunc, NULL) != 0)
        {
            printf("Creating consumer %d error.\n", i);
            exit(1);
        }

    for (int i = 0; i < MProducer; ++i) pthread_join(producer[i], NULL);
    for (int i = 0; i < NConsumer; ++i) pthread_join(consumer[i], NULL);

    return 0;
}
