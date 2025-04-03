#include "avl_binary_tree.h"
#include <stdlib.h>
#include <stdio.h>

// 创建新节点
AVLNode *avl_create_node(int data)
{
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    if (!node)
        return NULL;
    node->data = data;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 获取节点高度
int avl_height(AVLNode *node)
{
    return node ? node->height : 0;
}

// 更新高度
int avl_update_height(AVLNode *node)
{
    return max(avl_height(node->left), avl_height(node->right)) + 1;
}

// 计算平衡因子
int avl_get_balance_factor(AVLNode *node)
{
    if (!node)
        return 0;
    return avl_height(node->left) - avl_height(node->right);
}

// 最大值辅助函数
int max(int a, int b)
{
    return a > b ? a : b;
}

// 右旋
AVLNode *avl_rotate_right(AVLNode *y)
{
    AVLNode *y_left = y->left;
    AVLNode *y_left_r = y_left->right;

    y->left = y_left_r;
    y_left->right = y;

    y->height = avl_update_height(y);
    y_left->height = avl_update_height(y->left);

    return y_left;
}

// 左旋
AVLNode *avl_rotate_left(AVLNode *x)
{
    AVLNode *x_right = x->right;
    AVLNode *x_right_l = x_right->left;

    x_right->left = x;
    x->right = x_right_l;

    x->height = avl_update_height(x);
    x_right->height = avl_update_height(x_right);

    return x_right;
}

// 重新平衡节点
AVLNode *avl_rebalance(AVLNode *node)
{
    int f = avl_get_balance_factor(node);

    // 左左
    if (f > 1 && avl_get_balance_factor(node->left) >= 0)
    {
        return avl_rotate_right(node);
    }

    // 左右
    if (f > 1 && avl_get_balance_factor(node->left) < 0)
    {
        node->left = avl_rotate_left(node->left);
        return avl_rotate_right(node);
    }

    // 右右
    if (f < -1 && avl_get_balance_factor(node->right) <= 0)
    {
        return avl_rotate_left(node);
    }

    // 右左
    if (f < -1 && avl_get_balance_factor(node->right) > 0)
    {
        node->right = avl_rotate_right(node->right);
        return avl_rotate_left(node);
    }

    return node;
}

// 插入节点
AVLNode *avl_insert(AVLNode *root, int data)
{
    if (!root) {
        return avl_create_node(data);
    }
    
    AVLNode *node = avl_create_node(data);
    if (!node)
        return root;
    if (root->data < data)
    {
        root->right = avl_insert(root->right, data);
    }
    else if (root->data > data)
    {
        root->left = avl_insert(root->left, data);
    }
    else
    {
        return root;
    }

    root->height = avl_update_height(root);
    return avl_rebalance(root);
}

// 查找最小节点
AVLNode *min_value_node(AVLNode *node)
{
    if (!node)
        return NULL;
    while (node->left)
    {
        node = node->left;
    }
    return node;
}

// 删除节点
AVLNode *avl_delete(AVLNode *root, int data)
{
    if (!root)
        return NULL;
    if (root->data > data)
    {
        root->left = avl_delete(root->left, data);
    }
    else if (root->data < data)
    {
        root->right = avl_delete(root->right, data);
    }
    else
    {
        if (!root->left && !root->right)
        {
            free(root);
            return NULL;
        }
        else if (!root->right)
        {
            AVLNode *min = root->left;
            root->data = min->data;
            root->left = avl_delete(root->left, min->data);
        }
        else
        {
            AVLNode *min = min_value_node(root->right);
            root->data = min->data;
            root->right = avl_delete(root->right, min->data);
        }
    }
    root->height = avl_update_height(root);
    return avl_rebalance(root);
}

// 查找节点
AVLNode *avl_search(AVLNode *root, int data)
{
    if (!root || root->data == data)
        return root;
    else if (root->data > data)
        return avl_search(root->left, data);
    else
        return avl_search(root->right, data);
}

// 销毁树
void avl_destroy_tree(AVLNode *root)
{
    if (!root)
        return;
    avl_destroy_tree(root->left);
    avl_destroy_tree(root->right);
    free(root);
}

// 遍历函数
void avl_preorder(AVLNode *root)
{
    if(root){
        printf("%d\n",root->data);
        avl_preorder(root->left);
        avl_preorder(root->right);
    }
}

void avl_inorder(AVLNode *root)
{
    if(root){
        avl_inorder(root->left);
        printf("%d\n",root->data);
        avl_inorder(root->right);
    }
}

void avl_postorder(AVLNode *root)
{
    if(root){
        avl_postorder(root->left);
        avl_postorder(root->right);
        printf("%d\n",root->data);
    }
}
