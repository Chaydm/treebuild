#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "src/arr_binary_tree.h"

#define ARR_SIZE 13

void test_abt()
{
    // 创建 abt
    int arr[ARR_SIZE] = {1, 12, 13, 22, INT_MAX, 27, 29, 33, 38, INT_MAX, INT_MAX, 44, 45};
    ArrayBinaryTree *abt = newArrayBinaryTree(arr, ARR_SIZE);

    // 打印容量
    int size = abt_length(abt);
    printf("size of abt is %d \n", size);

    // 获取值
    int valid_v = abt_val(abt, 2);
    int invalid_v = abt_val(abt, 100);
    printf("arr[%d] = %d /t arr[%d] = %d \n", 2, valid_v, 100, invalid_v);

    // 层序遍历
    int return_size = 0;
    int *level_order = abt_levelOrder(abt, &return_size);
    for (int i = 0; i < return_size; i++)
        printf("%d \t", level_order[i]);
    printf("\n");
    free(level_order);

    // 前序遍历
    level_order = abt_preOrder(abt, &return_size);
    for (int i = 0; i < return_size; i++)
        printf("%d \t", level_order[i]);
    printf("\n");
    free(level_order);

    // 中序
    level_order = abt_inOrder(abt, &return_size);
    for (int i = 0; i < return_size; i++)
        printf("%d \t", level_order[i]);
    printf("\n");
    free(level_order);

    // 后序
    level_order = abt_postOrder(abt, &return_size);
    for (int i = 0; i < return_size; i++)
        printf("%d \t", level_order[i]);
    printf("\n");

    free(level_order);

    // 内存释放
    delArrayBinaryTree(abt);
}

int main()
{
    test_abt();
    return 0;
}