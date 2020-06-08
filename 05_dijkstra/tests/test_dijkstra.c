#include <graph.h>
#include <time.h>
//#include <common/test_set.h>
#define NUM_TESTS 7
void int_printer(const void *value)
{
    printf("%d", (((node_type *)value)->key));
}

int random_int(size_t excluded, int limit)
{
    int random_node_indx = rand() % limit;
    while (random_node_indx == excluded)
    {
        random_node_indx = rand() % limit;
    }
    return random_node_indx;
}

int *allocate_int_random_array(const unsigned int num_of_elem) 
{ 
  int *A = (int *)malloc(sizeof(int)*num_of_elem);
  
  srand(10);
  for (unsigned int i = 0; i < num_of_elem; i++) {
    A[i] = rand();
  }
  return A;
}

double run_test_heap(graph_type* graph)
{
    double accum;
    struct timespec requestStart, requestEnd;
    clock_gettime(CLOCK_REALTIME, &requestStart);
    dijkstra_minheap(graph, graph->nodes);
    clock_gettime(CLOCK_REALTIME, &requestEnd);
    accum = (requestEnd.tv_sec - requestStart.tv_sec) +
          (requestEnd.tv_nsec - requestStart.tv_nsec) / 1E9;
    return accum;
}

double run_test_array(graph_type* graph)
{
    double accum;
    struct timespec requestStart, requestEnd;
    clock_gettime(CLOCK_REALTIME, &requestStart);
    dijkstra_array(graph, graph->nodes);
    clock_gettime(CLOCK_REALTIME, &requestEnd);
    accum = (requestEnd.tv_sec - requestStart.tv_sec) +
          (requestEnd.tv_nsec - requestStart.tv_nsec) / 1E9;
    return accum;
}

int main(int argc, char *argv[])
{
    printf("Setting up test sets...\n");
    fflush(stdout);
    srand(10);
    FILE* f = fopen("benchmark/benchmark_data.txt", "w");
    printf("Size\tDijkstra Heap\tDijkstra Array\n");
    fprintf(f, "Size\tDijkstra Heap\tDijkstra Array\n");
    for (size_t i = 7; i < NUM_TESTS + 7; i++)
    {
        size_t num_nodes = 2 << i;
        int num_of_adjacents = 1 * num_nodes / 7;
        int *keys = allocate_int_random_array(num_nodes);

        graph_type *graph = create_graph(num_nodes, keys);
        
        //for each vertex, set up its adj list
        for (size_t j = 0; j < num_nodes; j++)
        {
            int random_node_indx = random_int(j, num_nodes);

            linked_list *adj = create_linked_list((void *)graph->nodes + random_node_indx * sizeof(node_type),
                                                  sizeof(node_type), rand() % 400);
            for (size_t z = 1; z < num_of_adjacents; z++)
            {
                random_node_indx = random_int(j, num_nodes);
                while (in_list(adj, (void *)graph->nodes + random_node_indx * sizeof(node_type)))
                {
                    random_node_indx = random_int(j, num_nodes);
                }

                insert_new_node(adj, (void *)graph->nodes + random_node_indx * sizeof(node_type), rand() % 400);
            }

            graph->nodes[j].adjacents = adj;
        }
        double time_heap = run_test_heap(graph);
        double time_array = run_test_array(graph);
        printf("2^%ld\t%f\t%f\n", i, time_heap, time_array);
        fprintf(f, "2^%ld\t%f\t%f\n", i, time_heap, time_array);
        //print_graph(graph, int_printer);
        delete_graph(graph);
        free(keys);
    }
    fclose(f);
}