#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "src/circular_queue.h"

void test_q_init_capacity_zero(){

    queue* q = q_init(0);
    assert( q == NULL);
    q_free(q);
}

void test_q_init_capacity_neg(){

    queue* q = q_init(-1);
    assert( q == NULL);
    q_free(q);
}

void test_q_init_capacity(){

    queue* q = q_init(10);
    assert( q != NULL);
    assert( q->front == 0);
    assert( q->size == 0);
    assert( q->rear == 0);
    assert( q->queCapacity == 10);
    assert( q->nums != NULL);
    q_free(q);
}

void test_q_insert(){
    queue *q = q_init(4);
    statuCode s = q_insert(q,1);
    assert(s == SUCCEED);
    assert(q->size == 1);
    assert(q->front==0);
    assert(q->rear == 1);
    assert(q->queCapacity == 4);
    assert(q->nums[0] == 1);
    s = q_insert(q,2);
    assert(q->size == 2);
    assert(q->front==0);
    assert(q->rear == 2);
    assert(q->queCapacity == 4);
    assert(q->nums[0] == 1);
    assert(q->nums[1] == 2);
    q_insert(q,2);
    q_insert(q,2);
    s = q_insert(q,2);
    assert(s == QUEUE_FULL);
    s = q_free(q);
    assert(s == SUCCEED);
}

void test_q_put(){
    int data;
    queue *q =NULL;
    statuCode s = q_put(q,&data);
    assert(s ==NULL_POINTER);
    q = q_init(2);
    s = q_put(q,&data);
    assert(s == QUEUE_EMPTY );
    q_insert(q,1);
    q_insert(q,2);
    s = q_put(q,&data);
    assert(s == SUCCEED);
    assert(data == 1);
    s = q_put(q,&data);
    assert(data == 2);
    assert(q_is_empty(q)==1);
}

int main(){
    test_q_init_capacity();
    test_q_init_capacity_neg();
    test_q_init_capacity_zero();
    test_q_insert();
    test_q_put();
    printf("all test pass\n");
    return 0;
}