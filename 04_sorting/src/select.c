#include "select.h"
#include "quick_sort.h"
#include "swap.h"
#define ADDR(A, i, key_size) (A + (i) * (key_size))

int equal(const void *a, const void *b, total_order ord)
{
    return ord(a, b) && ord(b, a);
}

struct pair three_way_partition(void *A, size_t pivot, size_t left, size_t right, const size_t elem_size, total_order leq)
{

    struct pair bounds;
    swap(ADDR(A, pivot, elem_size), ADDR(A, left, elem_size), elem_size);
    pivot = left;
    left++;
    int num_of_repetitions = 0;
    while (left <= right)
    {
        //left<pivot
        if (leq(ADDR(A, left, elem_size), ADDR(A, pivot, elem_size)) &&
            //!((leq(ADDR(A, i, elem_size), ADDR(A, pivot, elem_size))) && (leq(ADDR(A, pivot, elem_size), ADDR(A, i, elem_size))))
            !equal(ADDR(A, left, elem_size), ADDR(A, pivot, elem_size), leq))
        {
            swap(ADDR(A, left, elem_size), ADDR(A, pivot - num_of_repetitions, elem_size), elem_size);
            pivot = left;
            left++;
        }
        //left>pivot
        else if (!(leq(ADDR(A, left, elem_size), ADDR(A, pivot, elem_size))))
        {
            swap(ADDR(A, left, elem_size), ADDR(A, right, elem_size), elem_size);
            right--;
        }
        //left==pivot
        else
        {
            pivot = left;
            left++;
            num_of_repetitions++;
        }
    }

    swap(ADDR(A, pivot, elem_size), ADDR(A, right, elem_size), elem_size);
    bounds.first = right - num_of_repetitions; // position element before the repeated values
    bounds.second = right; // position of the pivot
    return bounds;
}

unsigned int select_pivot(void *A, const unsigned int n,
                          const size_t elem_size, total_order leq)
{

    if (n <= 10)
    {
        quick_sort(A, n, elem_size, leq);
        return n / 2;
    }

    unsigned int chunks = n / 5, chunck_left;//, c_l;

    for (unsigned int c = 0; c < chunks; c++)
    {
        chunck_left = c * 5;
        quick_sort(ADDR(A, chunck_left, elem_size), 5, elem_size, leq);
        swap(ADDR(A, chunck_left + 2, elem_size), ADDR(A, c, elem_size), elem_size);
    }

    return select_index(A, chunks, chunks / 2, elem_size, leq);
}

unsigned int select_index(void *A, const unsigned int n,
                          const unsigned int i,
                          const size_t elem_size,
                          total_order leq)
{
    if (n <= 10)
    {
        quick_sort(A, n, elem_size, leq);
        return i;
    }

    unsigned int pivot = select_pivot(A, n, elem_size, leq);
    struct pair bounds = three_way_partition(A, pivot, 0, n - 1, elem_size, leq);
    if (i < bounds.first)
    {
        return select_index(A, bounds.first - 1, i, elem_size, leq);
    } 
    else if (i > bounds.second)
    {
        return select_index(ADDR(A, bounds.second, elem_size), n - bounds.second - 1, i, elem_size, leq);
    }
    else
    {
        return i;
    }
}

void quick_sort_select_aux(void *A, size_t left, size_t right,
                           const size_t elem_size, total_order leq)
{
    while (left < right)
    {
        unsigned int pivot_index = left + select_pivot(ADDR(A, left, elem_size), right - left, elem_size, leq);
        struct pair k = three_way_partition(A, pivot_index, left, right - 1, elem_size, leq);
        quick_sort_select_aux(A, left, k.first, elem_size, leq);
        left = k.second + 1;
    }
}

void quick_sort_select(void *A, const unsigned int n,
                       const size_t elem_size,
                       total_order leq)
{
    quick_sort_select_aux(A, 0, n, elem_size, leq);
}
