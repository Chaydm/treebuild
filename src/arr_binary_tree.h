# pragma once

// 数组表示下的二叉树结构体
typedef struct {
    int *tree;
    int size;
} ArrayBinaryTree;

// 构造函数
ArrayBinaryTree *newArrayBinaryTree(int *arr, int arrSize) ;

// 析构函数
void delArrayBinaryTree(ArrayBinaryTree *abt);

// 树的size
int abt_length(ArrayBinaryTree *abt);

// 获取索引为 i 节点的值 
int abt_val(ArrayBinaryTree *abt, int i) ;

// 层序遍历 
int *abt_levelOrder(ArrayBinaryTree *abt, int *returnSize) ;

// 前序遍历
int *abt_preOrder(ArrayBinaryTree *abt, int *returnSize) ;

// 中序遍历 
int *abt_inOrder(ArrayBinaryTree *abt, int *returnSize);

// 后序遍历
int *abt_postOrder(ArrayBinaryTree *abt, int *returnSize);
