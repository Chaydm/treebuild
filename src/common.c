#include "common.h"

int arr_sum(int *arr, int lenth)
{
    int sum = 0;
    for(int i = 0;i<lenth;i++)
    {
        sum += *(arr+i);
    }
    return sum;
}
