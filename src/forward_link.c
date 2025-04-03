#include <stdio.h>
#include <stdlib.h>

#include "forward_link.h"

forward_link *create_node(int data)
{
    forward_link *node = (forward_link *)malloc(sizeof(forward_link));
    if (!node)
    {
        printf("malloc error!");
        return NULL;
    }
    node->data = data;
    node->next = NULL; // 这里必须手动初始化
    return node;
}

int insert_at_head(forward_link **head, int data)
{
    if (!head)
    {
        return -1;
    }
    forward_link *new_node = create_node(data);
    if (!new_node)
    {
        printf("create new node error!");
        return 0;
    }
    new_node->next = *head;
    *head = new_node;
    return 1;
}

void append(forward_link **head, int data)
{
    if (!head)
    {
        printf("head is NULL");
        return;
    }
    forward_link *new_node = create_node(data);
    if (!new_node)
    {
        printf("create new node error!");
        return;
    }
    if(!(*head)){
        *head = new_node;
        return;
    }
    forward_link *cur_p = *head;
    while (cur_p->next)
    {
        cur_p = cur_p->next;
    }
    cur_p->next = new_node;
    return;
}

void delete_node(forward_link **head, int data)
{
    if (!head)
    {
        printf("head is null");
        return;
    }
    forward_link *pre_p = NULL;
    forward_link *cur_p = *head;
    while (cur_p && cur_p->data != data)
    {
        pre_p = cur_p;
        cur_p = cur_p->next;
    }
    if (!cur_p)
    {
        printf("notfound a node data with %d", data);
        return;
    }
    if (!pre_p)
    { /* 头指针是目标元素*/
        *head = cur_p->next;
    }
    else
    {
        pre_p->next = cur_p->next;
    }
    free(cur_p);

    return;
}

int get_length(forward_link *head)
{
    int length = 0;
    forward_link *cur = head;
    while (cur)
    {
        length++;
        cur = cur->next;
    }

    return length;
}

void print_list(forward_link *head)
{
    int num = 0;
    forward_link *cur = head;
    while (cur)
    {
        num++;
        printf("第%d个元素是:%d \n", num, cur->data);
        cur = cur->next;
    }
    return;
}

void free_list(forward_link *head)
{
    forward_link *cur = head;
    while (cur)
    {
        head = head->next;
        free(cur);
        cur = head;
        /* code */
    }
    return;
}
