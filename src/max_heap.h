#pragma once

/**
 * 最大堆数据结构
 */
typedef struct _MaxHeap {
    int *heaparr;  // 堆数组
    int size;      // 当前堆大小
    int capacity;  // 堆容量
} MaxHeap;

/**
 * 初始化最大堆
 * @param capacity 初始容量
 * @return 初始化后的堆指针
 */
MaxHeap* max_heap_init(int capacity);

/**
 * 销毁最大堆
 * @param heap 堆指针
 */
void max_heap_destroy(MaxHeap *heap);

/**
 * 向堆中插入元素
 * @param heap 堆指针
 * @param value 要插入的值
 * @return 成功返回1，失败返回0
 */
int max_heap_insert(MaxHeap *heap, int value);

/**
 * 删除并返回堆顶元素(最大值)
 * @param heap 堆指针
 * @return 堆顶元素值
 */
int max_heap_extract(MaxHeap *heap);

/**
 * 获取堆顶元素(不删除)
 * @param heap 堆指针
 * @return 堆顶元素值
 */
int max_heap_peek(MaxHeap *heap);

/**
 * 获取堆当前大小
 * @param heap 堆指针
 * @return 堆大小
 */
int max_heap_size(MaxHeap *heap);

/**
 * 检查堆是否为空
 * @param heap 堆指针
 * @return 空返回1，否则返回0
 */
int max_heap_is_empty(MaxHeap *heap);

/**
 * 堆排序
 * @param arr 待排序数组
 * @param size 数组大小
 */
void max_heap_sort(int *arr, int size);

/**
 * topk (取出最小的k个数)
 * @param arr 待排序数组
 * @param size 数组大小
 * @param k 
 * @return 数组指针
 */
int *top_k_heap(int* arr,int size,int k);

/**
 * 层序遍历
 * @param heap 待遍历的堆
 */
void max_heap_order(MaxHeap* heap);


// 内部使用的辅助函数
void _max_heapify_up(MaxHeap *heap, int index);
void _max_heapify_down(MaxHeap *heap, int index);
int _max_heap_resize(MaxHeap *heap, int new_capacity);
int _left(int index);
int _right(int index);
int _parent(int index);

