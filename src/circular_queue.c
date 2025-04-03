#include <stdio.h>
#include <stdlib.h>
#include "circular_queue.h"

// 创建队列
queue *q_init(int queCapacity)
{
    if (queCapacity <= 0)
    {
        fprintf(stderr, "Capacity can not less than 1\n");
        return NULL;
    }

    queue *q = (queue *)malloc(sizeof(queue));
    if (!q)
    {
        fprintf(stderr, "create queue error !\n");
        return NULL;
    }
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->queCapacity = queCapacity;
    int *arr = (int *)calloc(queCapacity, sizeof(int));
    if (!arr)
    {
        fprintf(stderr, "create queue error!\n");
        free(q); // 注意要释放指针
        return NULL;
    }
    q->nums = arr;
    pthread_mutex_init(&q->lock, NULL);
    return q;
}

// 入队
statuCode q_insert(queue *q, int data)
{
    if (!q)
    {
        fprintf(stderr, "input queue pointer is NULL\n");
        return NULL_POINTER;
    }

    pthread_mutex_lock(&q->lock);
    if (q_is_full(q))
    {
        pthread_mutex_unlock(&q->lock);
        return QUEUE_FULL;
    }
    q->nums[q->rear] = data;
    q->size++;
    q->rear = (q->rear + 1) % q->queCapacity;
    pthread_mutex_unlock(&q->lock);
    return SUCCEED;
}

// 满队?
int q_is_full(queue *q)
{
    if (!q)
    {
        fprintf(stderr, "input queue pointer is NULL\n");
        return -1;
    }
    return (q->size == q->queCapacity);
}

// 空队？
int q_is_empty(queue *q)
{
    if (!q)
    {
        fprintf(stderr, "input queue pointer is NULL\n");
        return -1;
    }
    return (q->size == 0);
}

// 出队
statuCode q_put(queue *q, int *data)
{
    if (!q)
    {
        fprintf(stderr, "input queue pointer is NULL\n");
        return NULL_POINTER;
    }

    pthread_mutex_lock(&q->lock);
    if (q_is_empty(q))
    {
        pthread_mutex_unlock(&q->lock);
        return QUEUE_EMPTY;
    }
    *data = q->nums[q->front];
    q->size--;
    q->front = (q->front + 1) % q->queCapacity;
    pthread_mutex_unlock(&q->lock);
    return SUCCEED;
}

// 打印队列
void q_print(queue *q)
{
    if (!q)
    {
        fprintf(stderr, "input queue pointer is NULL\n");
        return;
    }

    pthread_mutex_lock(&q->lock);
    int p = 1;
    int index = q->front;
    for (int i = 0; i < q->size; i++)
    {
        printf("[%d] %d \n", p++, q->nums[index]);
        index = (index + 1) % q->queCapacity;
    }
    pthread_mutex_unlock(&q->lock);
}

// 释放队列
statuCode q_free(queue *q)
{
    if (!q)
        return NULL_POINTER;
    pthread_mutex_destroy(&q->lock);
    free(q->nums);
    free(q);
    return SUCCEED;
}
