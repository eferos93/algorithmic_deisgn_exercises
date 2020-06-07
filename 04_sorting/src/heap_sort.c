#include "heap_sort.h"
#include "swap.h"
#define ADDR(A, i, key_size) (A+(i)*(key_size))

void heap_sort(void *A, const unsigned int n, 
               const size_t elem_size, 
               total_order leq)
{
    binheap_type *h = build_heap(A, n, n, elem_size, geq_int);

    for (size_t i = n-1; i > 0; i--)
    {
        //swap(ADDR(A, i, elem_size), (void *)extract_min(h), elem_size);
        extract_min(h);
    }
    
}