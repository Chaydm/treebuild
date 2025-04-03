#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "binary_tree.h"

// 辅助函数：找到子树的最小节点
binary_tree *find_min(binary_tree *node)
{
    if (!node)
        return NULL;
    while (node->lchild)
    {
        node = node->lchild;
    }
    return node;
}

/// 创建新节点 (O(1))
binary_tree *create_treenode(int data)
{
    binary_tree *node = (binary_tree *)malloc(sizeof(binary_tree));
    if (!node)
    {
        fprintf(stderr, "create new node error");
        return NULL;
    }
    node->data = data;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

/// 插入节点 (O(n))
void insert_node(binary_tree **root_node, int data)
{
    if (!root_node)
        return;

    if (!(*root_node))
    {
        *root_node = create_treenode(data);
        return;
    }

    if (data < (*root_node)->data)
    {
        insert_node(&((*root_node)->lchild), data);
    }
    else
    {
        insert_node(&((*root_node)->rchild), data);
    }
}

/// 删除节点 (O(n))
void remove_node(binary_tree **root_node, int data)
{
    if (!root_node || !(*root_node))
        return;

    binary_tree *current = *root_node;

    if (data < current->data)
    {
        remove_node(&(current->lchild), data);
    }
    else if (data > current->data)
    {
        remove_node(&(current->rchild), data);
    }
    else
    {
        if (current->lchild && current->rchild)
        {
            binary_tree *min_node = find_min(current->rchild);
            if (!min_node)
                return;
            current->data = min_node->data;
            remove_node(&(current->rchild), min_node->data);
        }
        else if (current->lchild)
        {
            *root_node = current->lchild;
            free(current);
        }
        else if (current->rchild)
        {
            *root_node = current->rchild;
            free(current);
        }
        else
        {
            *root_node = NULL;
            free(current);
        }
    }
}

/// 查找节点 (O(n))
binary_tree *find_node(binary_tree *root_node, int data)
{
    if (!root_node)
        return NULL;
    if (root_node->data == data)
        return root_node;
    else if (root_node->data > data)
        return find_node(root_node->lchild, data);
    else
        return find_node(root_node->rchild, data);
}

/// 获取树的高度 (O(n))
int get_height(binary_tree *root_node)
{
    if (!root_node)
        return 0;
    return max(get_height(root_node->lchild), get_height(root_node->rchild)) + 1;
}

/// 获取节点个数 (O(n))
int get_size(binary_tree *root_node)
{
    if (!root_node)
        return 0;
    return 1 + get_size(root_node->lchild) + get_size(root_node->rchild);
}

/// 前序遍历 (O(n))
void pre_order(binary_tree *root_node, void (*visit)(binary_tree *))
{
    if (!root_node || !visit)
        return;
    visit(root_node);
    pre_order(root_node->lchild, visit);
    pre_order(root_node->rchild, visit);
}

/// 中序遍历 (O(n))
void in_order(binary_tree *root_node, void (*visit)(binary_tree *))
{
    if (!root_node || !visit)
        return;
    in_order(root_node->lchild, visit);
    visit(root_node);
    in_order(root_node->rchild, visit);
}

/// 后序遍历 (O(n))
void post_order(binary_tree *root_node, void (*visit)(binary_tree *))
{
    if (!root_node || !visit)
        return;
    post_order(root_node->lchild, visit);
    post_order(root_node->rchild, visit);
    visit(root_node);
}

/// 层次遍历 (O(n))
void level_order(binary_tree *root_node, void (*visit)(binary_tree *))
{
    if (!root_node || !visit)
        return;

    int capacity = 16;
    int front = 0, end = 0;
    binary_tree **queue = (binary_tree **)malloc(capacity * sizeof(binary_tree *));
    if (!queue)
        return;

    queue[end++] = root_node;
    while (front < end)
    {
        // 动态扩容
        if (end >= capacity)
        {
            capacity *= 2;
            binary_tree **new_queue = (binary_tree **)realloc(queue, capacity * sizeof(binary_tree *));
            if (!new_queue)
            {
                free(queue);
                return;
            }
            queue = new_queue;
        }

        binary_tree *current = queue[front++];
        visit(current);

        if (current->lchild)
            queue[end++] = current->lchild;
        if (current->rchild)
            queue[end++] = current->rchild;
    }

    free(queue);
}

/// 释放整棵树 (O(n))
void free_tree(binary_tree *root_node)
{
    if (!root_node)
        return;
    free_tree(root_node->lchild);
    free_tree(root_node->rchild);
    free(root_node);
}

/// @brief 完美二叉树(满二叉树) 1.只有最后一层全为叶子节点 2.其余层节点度为2
/// @param root_node
/// @return
int is_perfect_binary_tree(binary_tree *root_node)
{
    /*
        判断根节点高度和树的size 的关系 size = 2^h-1
    */
    // return 0;
    if (!root_node)
    {
        return -1;
    }
    int h = get_height(root_node);
    int size = get_size(root_node);
    if (size == (int)pow(2, h) - 1)
    {
        return 1;
    }
    return 0;
}

/// @brief 是否是完全二叉树
/// @param root_node 
/// @return 1:是完全二叉树 0:不是 -1:错误
int is_complete_binary_tree(binary_tree *root_node)
{
    if (!root_node)
        return 1;  // 空树认为是完全二叉树
    
    int capacity = 16;
    int front = 0, end = 0;
    binary_tree **queue = (binary_tree **)malloc(capacity * sizeof(binary_tree *));
    if (!queue)
        return -1;
    
    queue[end++] = root_node;
    int has_null = 0;  // 标记是否遇到空节点
    
    while (front < end) {
        // 动态扩容
        if (end >= capacity) {
            capacity *= 2;
            binary_tree **new_queue = (binary_tree **)realloc(queue, capacity * sizeof(binary_tree *));
            if (!new_queue) {
                free(queue);
                return -1;
            }
            queue = new_queue;
        }
        
        binary_tree *current = queue[front++];
        
        if (!current) {
            has_null = 1;
            continue;
        }
        
        // 如果已经遇到空节点后又遇到非空节点，则不是完全二叉树
        if (has_null && current) {
            free(queue);
            return 0;
        }
        
        // 将左右孩子入队，不管是否为NULL
        queue[end++] = current->lchild;
        queue[end++] = current->rchild;
    }
    
    free(queue);
    return 1;
}

/// @brief 是否是完满二叉树
/// @param root_node
/// @return
int is_full_binary_tree(binary_tree *root_node)
{
    if (!root_node)
        return -1;
    if (!root_node->lchild && !root_node->rchild)
        return 1;
    if (!root_node->lchild || !root_node->rchild)
        return 0;

    return is_full_binary_tree(root_node->lchild) && is_full_binary_tree(root_node->rchild);
}

/// @brief 是否是平衡二叉树
/// @param root_node
/// @return
int is_balance_binary_tree(binary_tree *root_node)
{
    if (!root_node)
        return -1;
    int l_height = root_node->lchild ? get_height(root_node->lchild) : 0;
    int r_height = root_node->rchild ? get_height(root_node->rchild) : 0;
    if (abs(l_height - r_height) > 1)
        return 0;
    if (!root_node->lchild || !root_node->rchild)
    {
        return 1;
    }
    return is_balance_binary_tree(root_node->lchild) && is_balance_binary_tree(root_node->rchild);
}

/// @brief 获取节点的父节点
/// @param root_node 树的根节点
/// @param node 要查找的节点
/// @return 父节点指针，NULL表示未找到或输入无效
binary_tree* get_parent(binary_tree *root_node, binary_tree *node)
{
    if (!root_node || !node || root_node == node)
        return NULL;
    
    if (root_node->lchild == node || root_node->rchild == node)
        return root_node;
    
    binary_tree *parent = get_parent(root_node->lchild, node);
    if (parent)
        return parent;
    
    return get_parent(root_node->rchild, node);
}

/// @brief 获取节点的兄弟节点
/// @param root_node 树的根节点
/// @param node 要查找的节点
/// @return 兄弟节点指针，NULL表示没有兄弟或输入无效
binary_tree* get_sibling(binary_tree *root_node, binary_tree *node)
{
    if (!root_node || !node)
        return NULL;
    
    binary_tree *parent = get_parent(root_node, node);
    if (!parent)
        return NULL;  // 根节点没有兄弟
    
    if (parent->lchild == node)
        return parent->rchild;
    else if (parent->rchild == node)
        return parent->lchild;
    else
        return NULL;  // 不应该发生的情况
}
