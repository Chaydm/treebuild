#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include "src/max_heap.h"

void test_heap_operations() {
    // 测试初始化
    MaxHeap* heap = max_heap_init(5);
    assert(heap != NULL);
    assert(max_heap_size(heap) == 0);
    assert(max_heap_is_empty(heap) == 1);

    // 测试插入和提取
    int test_data[] = {3, 1, 4, 1, 5, 9, 2, 6};
    for (int i = 0; i < 8; i++) {
        assert(max_heap_insert(heap, test_data[i]) == 1);
    }
    max_heap_order(heap);
    assert(max_heap_size(heap) == 8);
    assert(max_heap_peek(heap) == 9);

    // 测试提取顺序
    assert(max_heap_extract(heap) == 9);
    assert(max_heap_extract(heap) == 6);
    assert(max_heap_extract(heap) == 5);
    assert(max_heap_extract(heap) == 4);
    assert(max_heap_size(heap) == 4);

    // 测试空堆情况
    while (!max_heap_is_empty(heap)) {
        max_heap_extract(heap);
    }
    assert(max_heap_extract(heap) == INT_MAX);
    assert(max_heap_peek(heap) == INT_MAX);

    max_heap_destroy(heap);
}

void test_heap_sort() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int size = sizeof(arr)/sizeof(arr[0]);
    int expected[] = {9, 6, 5, 4, 3, 2, 1, 1};

    max_heap_sort(arr, size);

    for (int i = 0; i < size; i++) {
        assert(arr[i] == expected[i]);
    }
}

void test_top_k_heap(){
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int size = sizeof(arr)/sizeof(arr[0]);
    int expected[] = { 1, 1,2,3};

    int *res = top_k_heap(arr,size,4) ;

    for (int i = 0; i < 4; i++) {
        assert(res[i] == expected[i]);
    }
    free(res);
}

int main() {
    printf("开始测试最大堆...\n");
    
    test_heap_operations();
    test_heap_sort();
    test_top_k_heap();
    printf("所有测试通过!\n");
    return 0;
}
