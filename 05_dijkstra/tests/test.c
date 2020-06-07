#include <graph.h>
#include <time.h>
#include <common/test_set.h>
#define NUM_TESTS 10
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
    printf("Setting up test sets...");
    fflush(stdout);
    srand(10);
    printf("Size\tDijkstra Heap\tDijkstra Array\n");
    for (size_t i = 5; i < NUM_TESTS + 5; i++)
    {
        int num_nodes = 2 << i;
        int num_of_adjacents = 3 * num_nodes / 4;
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
        printf("2^5\t%d\t%d\n", time_heap, time_array);
        delete_graph(graph);
        free(keys);
    }
}