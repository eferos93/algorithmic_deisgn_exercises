#include "insertion_sort.h"
#include "swap.h"
#include <stdio.h>
#define ADDR(A, i, key_size) (A+(i)*(key_size))

void insertion_sort(void *A, const unsigned int n, 
                    const size_t elem_size, 
                    total_order leq)
{
    unsigned int j;
    for (unsigned int i = 1; i < n; i++)
    {
        j = i;
        while (j > 0 && leq(ADDR(A, j, elem_size), ADDR(A, j-1, elem_size)))
        {
            swap(ADDR(A, j-1, elem_size), ADDR(A, j, elem_size), elem_size);
            j--;
        }
    }
}