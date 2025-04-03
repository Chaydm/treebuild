#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>

#include "arr_binary_tree.h"

ArrayBinaryTree *newArrayBinaryTree(int *arr, int arrSize)
{
    if (!arr)
    {
        return NULL;
    }
    ArrayBinaryTree *newTree = (ArrayBinaryTree *)malloc(sizeof(ArrayBinaryTree));
    if (!newTree)
        return NULL;
    int *treeArr = (int *)malloc(arrSize * sizeof(int));
    if (!treeArr)
    {
        free(newTree);
        return NULL;
    }
    newTree->size = arrSize;
    memcpy(treeArr, arr, sizeof(int) * arrSize);
    newTree->tree = treeArr;
    return newTree;
}

void delArrayBinaryTree(ArrayBinaryTree *abt)
{
    if (!abt)
        return;
    free(abt->tree);
    free(abt);
}

int abt_length(ArrayBinaryTree *abt)
{
    int length = 0;
    for (int i = 0; i < abt->size; i++)
    {
        if(abt_val(abt,i)!= INT_MAX)
            length ++ ;
    }
    return length;
}

// 获取索引为 i 节点的值
int abt_val(ArrayBinaryTree *abt, int i)
{
    if (!abt || i >= abt->size)
    {
        return INT_MAX;
    }
    return abt->tree[i];
}

// 层序遍历
int *abt_levelOrder(ArrayBinaryTree *abt, int *returnSize)
{
    if (!abt || !returnSize)
        return NULL;
    int *arr = (int *)malloc(abt_length(abt) * sizeof(int));
    if (!arr)
        return NULL;
    int index = 0;
    for (int i = 0; i < abt->size; i++)
    {
        if (abt->tree[i] == INT_MAX)
            continue;
        arr[index++] = abt->tree[i];
    }
    *returnSize = index;
    return arr;
}

// 返回左节点的位置
static int left(int i)
{
    return 2 * i + 1;
}

// 返回右节点的位置
static int right(int i)
{
    return 2 * i + 2;
}

// 深度优先遍历
static void abt_dfs(ArrayBinaryTree *abt, int i, char *order, int *res, int *index)
{
    int value = abt_val(abt, i); //
    if (value == INT_MAX)
        return;
    if (strcmp(order, "pre") == 0)
        res[(*index)++] = value;
    abt_dfs(abt, left(i), order, res, index);
    if (strcmp(order, "in") == 0)
        res[(*index)++] = value;
    abt_dfs(abt, right(i), order, res, index);
    if (strcmp(order, "post") == 0)
        res[(*index)++] = value;
}

// 先序遍历
int *abt_preOrder(ArrayBinaryTree *abt, int *returnSize)
{
    if (!abt || !returnSize)
        return NULL;
    int *arr = (int *)malloc(abt_length(abt) * sizeof(int));
    if (!arr)
        return NULL;
    int index = 0;
    abt_dfs(abt, 0, "pre", arr, &index);
    *returnSize = index;
    return arr;
}

// 中序遍历
int *abt_inOrder(ArrayBinaryTree *abt, int *returnSize)
{
    if (!abt || !returnSize)
        return NULL;
    int *arr = (int *)malloc(abt_length(abt) * sizeof(int));
    if (!arr)
        return NULL;
    int index = 0;
    abt_dfs(abt, 0, "in", arr, &index);
    *returnSize = index;
    return arr;
}

// 后序遍历
int *abt_postOrder(ArrayBinaryTree *abt, int *returnSize)
{
    if (!abt || !returnSize)
        return NULL;
    int *arr = (int *)malloc(abt_length(abt)* sizeof(int));
    if (!arr)
        return NULL;
    int index = 0;
    abt_dfs(abt, 0, "post", arr, &index);
    *returnSize = index ;
    return arr;
}
