#include "queue.h"
#include <stdlib.h>

Queue *init_queue() {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (!queue) return NULL;
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

void free_queue(Queue *queue) {
    if (!queue) return;
    QueueNode *current = queue->front;
    while (current) {
        QueueNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(queue);
}

void enqueue(Queue *queue, int data) {
    if (!queue) return;
    QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
    if (!node) return;
    node->data = data;
    node->next = NULL;
    
    if (queue->rear) {
        queue->rear->next = node;
    } else {
        queue->front = node;
    }
    queue->rear = node;
    queue->size++;
}

int dequeue(Queue *queue) {
    if (!queue || !queue->front) return -1;
    QueueNode *temp = queue->front;
    int data = temp->data;
    queue->front = temp->next;
    if (!queue->front) {
        queue->rear = NULL;
    }
    free(temp);
    queue->size--;
    return data;
}

int is_empty_queue(Queue *queue) {
    return queue == NULL || queue->front == NULL;
}
