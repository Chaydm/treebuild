#include "stack.h"
#include <stdlib.h>

Stack *init_stack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack) return NULL;
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void free_stack(Stack *stack) {
    if (!stack) return;
    StackNode *current = stack->top;
    while (current) {
        StackNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(stack);
}

void push(Stack *stack, int data) {
    if (!stack) return;
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    if (!node) return;
    node->data = data;
    node->next = stack->top;
    stack->top = node;
    stack->size++;
}

int pop(Stack *stack) {
    if (!stack || !stack->top) return -1;
    StackNode *temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return data;
}

int is_empty_stack(Stack *stack) {
    return stack == NULL || stack->top == NULL;
}
