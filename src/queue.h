#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

typedef struct QueueNode {
    int data;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
    int size;
} Queue;

Queue *init_queue();
void free_queue(Queue *queue);
void enqueue(Queue *queue, int data);
int dequeue(Queue *queue);
int is_empty_queue(Queue *queue);

#endif
