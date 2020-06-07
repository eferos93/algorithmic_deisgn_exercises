#include <stdio.h>

#include "insertion_sort.h"
#include "quick_sort.h"
#include "select.h"
#include "bubble_sort.h"
#include "selection_sort.h"
#include "heap_sort.h"
#include "utilities.h"

#define MAX_SIZE_ALL (1<<13)
#define MAX_SIZE_NLOGN (1<<20)
#define ARRAY_SIZE (1<<23)

#define NUM_OF_REPETITIONS 15

void test_and_print(void (*sort)(void *A, const unsigned int n, 
                         const size_t elem_size, 
                         total_order leq), 
                    const void *A, const unsigned int n, 
                    const size_t elem_size, total_order leq, 
                    const unsigned int rep, FILE *f)
{
    int sorted;

    double elapsed_time = test(sort,A,n,elem_size,leq,rep,&sorted);
    printf("\t%lf", elapsed_time);
    fprintf(f, "\t%lf", elapsed_time);
    if (!sorted) {
        printf(" (KO)");
    }
    fflush(stdout);
}


int main(int argc, char *argv[])
{
    int *A=get_random_int_array(ARRAY_SIZE);
    int *A_sorted=malloc(sizeof(int)*ARRAY_SIZE);
    int *A_rev_sorted=malloc(sizeof(int)*ARRAY_SIZE);

    for (unsigned int i=0; i<ARRAY_SIZE; i++) {
        A_sorted[i]=i;
        A_rev_sorted[i]=ARRAY_SIZE-i;
    }
    
    FILE *f_insert_sort = fopen("benchmark_plot/insert_sort.txt", "w");
    FILE *f_quick_sort = fopen("benchmark_plot/quicksort.txt", "w");
    FILE *f_all = fopen("benchmark_plot/all.txt", "w");
    FILE *f_quick_vs_heap = fopen("benchmark_plot/quick_vs_heap.txt", "w");

    unsigned int i;
    printf("Size\tInsertion Sort\t          \t        \n");
    printf("    \t(Random Case)\t(Best Case)\t(Worst Case)");
    fprintf(f_insert_sort, "Size\tinsert_sort_random\tinsert_sort_best\tinsert_sort_worst");
    for (i=2; (1<<i)<=MAX_SIZE_ALL; i++) {
        const unsigned int A_size=1<<i;
        printf("\n2^%d",i);
        fprintf(f_insert_sort, "\n2^%d",i);
        test_and_print(insertion_sort, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f_insert_sort);
        test_and_print(insertion_sort, A_sorted,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f_insert_sort);
        test_and_print(insertion_sort, A_rev_sorted,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f_insert_sort);
    }
    printf("\n\n\n");
    fclose(f_insert_sort);

    printf("Size\tQuick Sort\t           \tQuick Sort + Select\n");
    printf("    \t(Random Case)\t(Worst Case)\t(Random Case)\t(Worst Case)");
    fprintf(f_quick_sort, "Size\tquick_random\tquick_worst\tquick+select_random\tquick+select_worst");
    for (i=2; (1<<i)<=MAX_SIZE_ALL; i++) {
        const unsigned int A_size=1<<i;
        printf("\n2^%d",i);
        fprintf(f_quick_sort, "\n2^%d",i);
        test_and_print(quick_sort, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f_quick_sort);
        test_and_print(quick_sort, A_sorted,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f_quick_sort);
        test_and_print(quick_sort_select, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f_quick_sort);
        test_and_print(quick_sort_select, A_sorted,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f_quick_sort);
    }
    printf("\n\n\n");
    fclose(f_quick_sort);

    printf("Size\tInsertion Sort\tQuick Sort\tBubble Sort\tSelection Sort\tHeap Sort\n");
    printf("    \t(Random Case)\t(Random Case)\t\t\t");
    fprintf(f_all, "Size\tinsert_sort_random\tquick_random\tbubble\tselection_sort\theap_sort");
    for (i=2; (1<<i)<=MAX_SIZE_ALL; i++) {
        const unsigned int A_size=1<<i;
        printf("\n2^%d",i);
        fprintf(f_all, "\n2^%d",i);
        test_and_print(insertion_sort, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f_all);
        test_and_print(quick_sort, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f_all);
        test_and_print(bubble_sort, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f_all);
        test_and_print(selection_sort, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f_all);
        test_and_print(heap_sort, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f_all);
    }
    printf("\n\n\n");
    fclose(f_all);

    printf("Size\tQuick Sort\tQuick Sort +\tHeap Sort\n");
    printf("    \t          \t  Select\n");
    printf("    \t(Random Case)\t(Random Case)\t");
    fprintf(f_quick_vs_heap, "Size\tquick_random\tquick+select_random\theap_sort");
    for (; (1<<i)<=MAX_SIZE_NLOGN; i++) {
        const unsigned int A_size=1<<i;
        printf("\n2^%d",i);
        fprintf(f_quick_vs_heap, "\n2^%d",i);
        test_and_print(quick_sort, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f_quick_vs_heap);
        test_and_print(quick_sort_select, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f_quick_vs_heap);
        test_and_print(heap_sort, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f_quick_vs_heap);
    }

    printf("\n");
    fclose(f_quick_vs_heap);
    free(A);
    free(A_sorted);
    free(A_rev_sorted);

    return 0;
}