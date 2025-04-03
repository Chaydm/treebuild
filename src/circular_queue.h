#pragma once
#include <pthread.h>

/// 状态码
typedef enum
{
    FAILD = 0,
    // 成功
    SUCCEED,
    // 满队
    QUEUE_FULL,
    // 空队
    QUEUE_EMPTY,
    NULL_POINTER

} statuCode;

/*
* 实现循环队列的增删改查
*/

typedef struct _queue
{
    int *nums; //存储队列的数组
    int front; //头指针
    int rear;//尾指针
    int size; //队列的大小
    int queCapacity; // 队列容量
    pthread_mutex_t lock; // 互斥锁
}queue;

// 创建队列
queue*  q_init(int queCapacity);

// 入队
statuCode q_insert(queue *q,int data);

// 判断队列是否满队 -1 读取队列失败
int q_is_full(queue *q);

// 判断队列是否空队 -1 读取队列失败
int q_is_empty(queue *q);

// 出队
statuCode q_put(queue *q,int *data);

// 遍历队列
void q_print( queue *q);

// 释放队列
statuCode q_free(queue *q);
