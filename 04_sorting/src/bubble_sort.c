#include "bubble_sort.h"
#include "swap.h"
#define ADDR(A, i, key_size) (A+(i)*(key_size))

void bubble_sort(void *A, const unsigned int n, 
                 const size_t elem_size, 
                 total_order leq)
{
    for (size_t i = n-1; i > 0; i--)
    {
        for (size_t j = 0; j < i; j++)
        {
            if (!leq(ADDR(A, j, elem_size), ADDR(A, j+1, elem_size)))
            {
                swap(ADDR(A, j, elem_size), ADDR(A, j+1, elem_size), elem_size);                
            }
            
        }
        
    }
    
}