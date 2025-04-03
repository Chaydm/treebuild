#pragma once

typedef struct _AVLNode {
    int data;
    int height;
    struct _AVLNode *left;
    struct _AVLNode *right;
} AVLNode;

// 
AVLNode* avl_create_node(int data);
void avl_destroy_tree(AVLNode *root);

// 插入删除
AVLNode* avl_insert(AVLNode *root, int data);
AVLNode* avl_delete(AVLNode *root, int data);

// 查询
AVLNode* avl_search(AVLNode *root, int data);

// 遍历
void avl_preorder(AVLNode *root);
void avl_inorder(AVLNode *root);
void avl_postorder(AVLNode *root);

// 恢复平衡
AVLNode* avl_rebalance(AVLNode *node);

static AVLNode *avl_rotate_left(AVLNode *node);
static AVLNode *avl_rotate_right(AVLNode *node);
