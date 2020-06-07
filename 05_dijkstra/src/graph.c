#include <graph.h>
#include <stdio.h>


node_type *create_nodes(size_t num_of_nodes, int* keys)
{
    node_type *new_nodes = (node_type *)malloc(sizeof(node_type)*num_of_nodes);
    for (size_t i = 0; i < num_of_nodes; i++)
    {
        //new_nodes[i] = create_node(i, adj_lists+(i*sizeof(linked_list)));
        //new_nodes[i] = create_node(keys[i]);
        new_nodes[i].adjacents = NULL;
        new_nodes[i].key = keys[i];
        new_nodes[i].distance_from_source = UINT_MAX;
        new_nodes[i].predecessor = NULL;
    }

    return new_nodes;
}

graph_type *create_graph(size_t num_nodes, int * keys)
{
    graph_type *graph = (graph_type *)malloc(sizeof(graph_type));
    graph->num_nodes = num_nodes;
    graph->nodes = create_nodes(num_nodes, keys);
    /*graph->nodes = (node_type*) malloc(sizeof(node_type)*num_nodes);
    for (size_t i = 0; i < num_nodes; i++)
    {
        graph->nodes[i].key = keys[i];
        graph->nodes[i].adjacents = NULL;
        graph->nodes[i].distance_from_source = UINT_MAX;
        graph->nodes[i].predecessor = NULL;
    }
    */
    return graph;
}

void initialise(graph_type *g)
{
    for (size_t i = 0; i < g->num_nodes; i++)
    {
        //(g->nodes[i]).key = i;
        g->nodes[i].distance_from_source = UINT_MAX;
        g->nodes[i].predecessor = NULL;
    }
}

void update_distance(binheap_type *queue, node_type *node, unsigned int new_distance)
{
    decrease_key(queue, (void*) node, &(new_distance));
}

/**
 * @brief Relax for min-heap implementation
 * @param u Starting node
 * @param v Node which distance is to be updated
 * @param weight Weight between u and v
 */
void relax(binheap_type *queue, node_type *u, node_type *v, unsigned int weight)
{
    if (u->distance_from_source + weight < v->distance_from_source)
    {
        update_distance(queue, v, u->distance_from_source + weight);
        v->predecessor = u;
    }
}

/**
 * @brief Relax for vector implementation
 * @param u Starting node
 * @param v Node which distance is to be updated
 * @param weight Weight between u and v
 */
void relax_array(node_type *u, node_type *v, size_t weight)
{
    if (u->distance_from_source + weight < v->distance_from_source)
    {
        v->distance_from_source = u->distance_from_source + weight;
        v->predecessor = u;
    }
}

int order_node(const void* node_a, const void* node_b)
{
    return leq_int((void *) &(((node_type*) node_a)->distance_from_source), (void *) &(((node_type*) node_b)->distance_from_source));
}


void dijkstra_minheap(graph_type* g, node_type* source)
{
    initialise(g);
    source->distance_from_source = 0;
    binheap_type* queue = build_heap((void*) g->nodes, g->num_nodes, g->num_nodes, sizeof(node_type), order_node);

    while (!is_heap_empty(queue))
    {
        node_type* u = (node_type*) extract_min(queue);
        list_node* current = u->adjacents->head;
        while (current)
        {
            relax(queue, u, current->element, current->weight);
            current = current->next;
        }
    }
    delete_heap(queue);
}

node_type* extract_min_array(linked_list* nodes)
{    
    list_node* min = nodes->head;
    list_node* before_min = NULL;
    list_node* current = min->next;
    list_node* before_current = min;
    node_type* curr_node;
    node_type* min_node = (node_type*) min->element;

    while (current)
    {
        curr_node = (node_type*) current->element;
        if (curr_node->distance_from_source < min_node->distance_from_source)
        {
            min = current;
            min_node = (node_type*) min->element;
            before_min = before_current;
        }
        before_current = current;
        current = current->next;
    }

    if (before_min)
    {
        before_min->next = min->next;
    }
    
    free(min);
    nodes->length--;
    return min_node;
}

linked_list* build_array(void* elements, size_t num_of_elem, size_t elem_size)
{
    linked_list* list = create_linked_list(elements, elem_size, 0);
    for (size_t i = 1; i < num_of_elem; i++)
    {
        insert_new_node(list, elements+(i*elem_size), 0);
    }
    return list;
}

void dijkstra_array(graph_type* g, node_type* source)
{
    initialise(g);
    source->distance_from_source = 0;
    
    linked_list* queue = build_array((void *) g->nodes, g->num_nodes, sizeof(node_type));

    while (queue->length != 0)
    {
        node_type* u = extract_min_array(queue);
        list_node* current = u->adjacents->head;
        while (current)
        {
            relax_array(u, current->element, current->weight);
            current = current->next;
        }
    }
    printf("%ld", queue->head);
    free(queue);
    //delete_linked_list(queue);
}


void delete_graph(graph_type* g)
{
    for (size_t i = 0; i < g->num_nodes; i++)
    {
        delete_linked_list(g->nodes[i].adjacents);
    }
    free(g->nodes);
    free(g);
}

void print_graph(graph_type* g, void (*key_printer)(const void *value))
{
    printf("\n");
    for (size_t i = 0; i < g->num_nodes; i++)
    {
        printf("(key: ");
        printf("%d", g->nodes[i].key);
        printf(")");
        print_list(g->nodes[i].adjacents, key_printer);
        printf("\n");
    }
    
}