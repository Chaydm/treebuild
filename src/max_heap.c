#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>

#include "max_heap.h"

MaxHeap *max_heap_init(int capacity)
{
    MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
    if (!heap)
        return NULL;
    heap->heaparr = (int *)malloc(capacity * sizeof(int));
    if (!heap->heaparr)
    {
        free(heap);
        return NULL;
    }
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void max_heap_destroy(MaxHeap *heap)
{
    if (heap)
    {
        free(heap->heaparr);
        free(heap);
    }
}

int max_heap_insert(MaxHeap *heap, int value)
{
    if (!heap)
        return 0;
    if (heap->size == heap->capacity)
    {
        int result = _max_heap_resize(heap, heap->capacity * 2);
        if (!result)
            return 0;
    }

    heap->heaparr[heap->size++] = value;
    _max_heapify_up(heap, heap->size - 1);
    return 1;
}

int max_heap_extract(MaxHeap *heap)
{
    if (!heap || !heap->size)
    {
        return INT_MAX;
    }
    int result = heap->heaparr[0];
    heap->heaparr[0] = heap->heaparr[heap->size - 1];
    heap->size--;
    _max_heapify_down(heap, 0);
    return result;
}

int max_heap_peek(MaxHeap *heap)
{
    if (!heap || !heap->size)
    {
        return INT_MAX;
    }
    return heap->heaparr[0];
}

int max_heap_size(MaxHeap *heap)
{
    if (!heap)
    {
        return -1;
    }
    return heap->size;
}

int max_heap_is_empty(MaxHeap *heap)
{
    if (!heap || !heap->size)
    {
        return 1;
    }
    return 0;
}

// 堆排序
void max_heap_sort(int *arr, int size)
{
    // 构建堆
    MaxHeap heap = {.capacity = size, .size = size};
    heap.heaparr = (int *)malloc(size * sizeof(int));
    if (!heap.heaparr)
        return;
    memcpy(heap.heaparr, arr, size * sizeof(int));
    for (int i = _parent(size - 1); i >= 0; i--)
        _max_heapify_down(&heap, i);

    // 排序
    int index = 0;
    while (heap.size)
    {
        arr[index++] = heap.heaparr[0];
        heap.heaparr[0] = heap.heaparr[heap.size - 1];
        heap.size--;
        _max_heapify_down(&heap, 0);
    }
    free(heap.heaparr);
}

// 上浮
void _max_heapify_up(MaxHeap *heap, int index)
{
    if (!heap) // 空堆
        return;

    while (_parent(index) >= 0 && heap->heaparr[_parent(index)] < heap->heaparr[index])
    {
        int temp = heap->heaparr[index];
        heap->heaparr[index] = heap->heaparr[_parent(index)];
        heap->heaparr[_parent(index)] = temp;
        index = _parent(index);
    }
}

// 下沉
void _max_heapify_down(MaxHeap *heap, int index)
{
    if (!heap)
        return;
    while (1)
    {
        int largest = index;
        int left = _left(index);
        int right = _right(index);

        if (left < heap->size && heap->heaparr[left] > heap->heaparr[largest])
            largest = left;
        if (right < heap->size && heap->heaparr[right] > heap->heaparr[largest])
            largest = right;
        if (largest == index)
            break;

        // 交换元素
        int temp = heap->heaparr[index];
        heap->heaparr[index] = heap->heaparr[largest];
        heap->heaparr[largest] = temp;
        index = largest;
    }
}

// 更新容量
int _max_heap_resize(MaxHeap *heap, int new_capacity)
{
    // 扩容
    int *temp = realloc(heap->heaparr, new_capacity * sizeof(int));
    if (!temp)
        return 0;
    heap->capacity = new_capacity;
    heap->heaparr = temp;
    return 1;
}

// 左孩位置
int _left(int index)
{
    return 2 * index + 1;
}

int _right(int index)
{
    return 2 * index + 2;
}

int _parent(int index)
{
    return (index - 1) / 2;
}

int *top_k_heap(int *arr, int size, int k)
{
    if (!arr || size < k)
        return NULL;
    // 取出前k个元素构建最大堆
    MaxHeap max = {.size = k, .capacity = k};
    max.heaparr = (int *)malloc(k * sizeof(int));
    if (!max.heaparr)
        return NULL;
    memcpy(max.heaparr, arr, k * sizeof(int));
    for (int i = _parent(max.size - 1); i >= 0; i--)
    {
        _max_heapify_down(&max, i);
    }

    for (int i = k; i < size; i++)
    {
        if (arr[i] < max.heaparr[0])
        {
            max.heaparr[0] = arr[i];
            _max_heapify_down(&max, 0);
        }
    }
    int *res = (int *)malloc(k * sizeof(int));
    if (!res)
        return NULL;
    for (int i = k - 1; i > 0; i--)
    {
        res[i] = max.heaparr[0];
        max.heaparr[0] = max.heaparr[i];
        max.size--;
        _max_heapify_down(&max, 0);
    }
    res[0] = max.heaparr[0];
    free(max.heaparr);
    return res;
}

void max_heap_order(MaxHeap *heap)
{
    if(!heap) return;
    for(int i = 0; i < heap->size ; i ++)
    {
        printf("%d \t",heap->heaparr[i]);
    }
    printf("\n");
}
