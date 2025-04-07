#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode *top;
    int size;
} Stack;

Stack *init_stack();
void free_stack(Stack *stack);
void push(Stack *stack, int data);
int pop(Stack *stack);
int is_empty_stack(Stack *stack);

#endif
