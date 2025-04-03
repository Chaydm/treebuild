#pragma once

typedef struct _forward_link {
    int data;
    struct _forward_link *next;
} forward_link;

// 创建新节点
forward_link* create_node(int data);

// 在头部插入节点
int insert_at_head(forward_link **head, int data);

// 在尾部插入节点
void append(forward_link **head, int data);

// 删除节点
void delete_node(forward_link **head, int data);

// 获取链表长度
int get_length(forward_link *head);

// 打印链表
void print_list(forward_link *head);

// 释放链表
void free_list(forward_link *head);
