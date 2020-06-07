#include "quick_sort.h"
#include "swap.h"
#define ADDR(A, i, key_size) (A+(i)*(key_size))

unsigned int partition(void *A, unsigned int left,
                       unsigned int right, unsigned int pivot_index,
                       const size_t elem_size, total_order leq)
{
    swap(ADDR(A, pivot_index, elem_size), ADDR(A, left, elem_size), elem_size);
    pivot_index = left;
    left++;

    while (left <= right)
    {
        if (!leq(ADDR(A, left, elem_size), ADDR(A, pivot_index, elem_size)))
        {
            swap(ADDR(A, left, elem_size), ADDR(A, right, elem_size), elem_size);
            right--;
        }
        else
        {
            left++;
        }
    }
    swap(ADDR(A, pivot_index, elem_size), ADDR(A, right, elem_size), elem_size);
    return right; //position of the pivot
}

void quick_sort_aux(void *A, unsigned int left, const unsigned int right,
                    const size_t elem_size, total_order leq)
{
    unsigned int pivot_index;
    while (left < right)
    {
        pivot_index = partition(A, left, right-1, left, elem_size, leq);
        quick_sort_aux(A, left, pivot_index, elem_size, leq);
        left = pivot_index + 1;
    }
}

void quick_sort(void *A, const unsigned int n,
                const size_t elem_size,
                total_order leq)
{
    quick_sort_aux(A, 0, n, elem_size, leq);
}