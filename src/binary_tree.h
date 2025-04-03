#ifndef BINARY_TREE_H
#define BINARY_TREE_H

// // 宏的每个参数和整体表达式均需用括号包裹，以强制运算顺序，避免优先级错误
// #define MAX(a,b)  ((a)>(b)?(a):(b))  // 这里必须打括号，不然和其他值混合运算会出错。 eg:MAX(a,b)+1 => a>b?a:b+1 而需要的是 (a>b?a:b)=1

/* 
 * 普通二叉树的增删改查
 * 时间复杂度:
 *   - 插入/删除/查找: O(n) 最坏情况
 *   - 遍历: O(n)
 */

typedef struct _binary_tree {
    int data;                   // 节点数据
    struct _binary_tree *lchild; // 左子树
    struct _binary_tree *rchild; // 右子树
} binary_tree;

static inline int max(int a,int b){return a>b?a:b;}

/// 创建新节点 (O(1))
binary_tree* create_treenode(int data);

/// 插入节点 (O(n))
void insert_node(binary_tree **root_node, int data);

/// 删除节点 (O(n)) 
void remove_node(binary_tree **root_node, int data);

/// 查找节点 (O(n))
binary_tree* find_node(binary_tree *root_node, int data);

/// 获取树的高度 (O(n))
int get_height(binary_tree *root_node);

/// 获取节点个数 (O(n))
int get_size(binary_tree *root_node);

/// 前序遍历 (O(n))
void pre_order(binary_tree *root_node, void (*visit)(binary_tree*));

/// 中序遍历 (O(n))
void in_order(binary_tree *root_node, void (*visit)(binary_tree*));

/// 后序遍历 (O(n))
void post_order(binary_tree *root_node, void (*visit)(binary_tree*));

/// 层次遍历 (O(n))
void level_order(binary_tree *root_node, void (*visit)(binary_tree*));

/// 释放整棵树 (O(n))
void free_tree(binary_tree *root_node);

/// @brief  是不是完美二叉树
/// @param root_node 
/// @return 
int is_perfect_binary_tree(binary_tree *root_node);

/// @brief 是否是完全二叉树
/// @param root_node 
/// @return 
int is_complete_binary_tree(binary_tree *root_node);


/// @brief 是否是完满二叉树
/// @param root_node 
/// @return 
int is_full_binary_tree(binary_tree *root_node);

/// @brief 是否是平衡二叉树
/// @param root_node 
/// @return 
int is_balance_binary_tree(binary_tree *root_node);

/// @brief 获取节点的父节点
/// @param root_node 树的根节点
/// @param node 要查找的节点
/// @return 父节点指针，NULL表示未找到或输入无效
binary_tree* get_parent(binary_tree *root_node, binary_tree *node);

/// @brief 获取节点的兄弟节点
/// @param root_node 树的根节点
/// @param node 要查找的节点
/// @return 兄弟节点指针，NULL表示没有兄弟或输入无效
binary_tree* get_sibling(binary_tree *root_node, binary_tree *node);

#endif // BINARY_TREE_H
