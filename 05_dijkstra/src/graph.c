#include <graph.h>


node_type *create_nodes(size_t num_of_nodes, linked_list* adj_lists)
{
    node_type *new_nodes = (node_type *)malloc(sizeof(node_type)*num_of_nodes);
    for (size_t i = 0; i < num_of_nodes; i++)
    {
        //new_nodes[i] = create_node(i, adj_lists+(i*sizeof(linked_list)));
        new_nodes[i] = create_node(i, NULL);
    }
    
    //new_node->key = key;
    //new_node->key_size = key_size;
    //new_node->distance_from_source = UINT_MAX;
    //new_node->predecessor = NULL;

    return new_nodes;
}

node_type create_node(int key, linked_list* adj_list)
{
    node_type new_node;// = (node_type*) malloc(sizeof(node_type));
    new_node.adjacents = adj_list;
    new_node.key = key;
    new_node.distance_from_source = UINT_MAX;
    new_node.predecessor = NULL;
    return new_node;
}

/*
unsigned int weight(graph_type *g, node_type *from, node_type *to)
{
    return g->weights_matrix[from->key * g->num_nodes + to->key];
}
*/
/*
int adjacents_len(graph_type* g, node_type* node)
{
    int n = 0;
    for(int i=0; i < g->num_nodes; i++)
    {
        if(g->nodes[i].key == node->key)
        { 
            continue;
        }
        n += (weight(g, node, &(g->nodes)[i])) < UINT_MAX;
    }
        
    return n;
}
*/
// returns nodes adjacent to a given node
/*
adjacents_type adjacents(graph_type *g, node_type *node, int n)
{
    node_type **adj_nodes = (node_type **)malloc(sizeof(node_type *) * n);
    int adj_index = 0;
    for (int i = 0; i < g->num_nodes; i++)
    {
        int weight_node_to_i = weight(g, node, &(g->nodes)[i]);
        if (weight_node_to_i < UINT_MAX && (g->nodes)[i].key != node->key)
        {
            adj_nodes[adj_index++] = &(g->nodes)[i];
        }
    }
    
    adjacents_type adj;
    adj.adj = adj_nodes;
    adj.length = adj_index;
    return adj;
}
*/
graph_type *create_graph(size_t num_nodes, linked_list* adj_lists)
{
    graph_type *graph = (graph_type *)malloc(sizeof(graph_type));
    graph->num_nodes = num_nodes;
    //graph->weights_matrix = adj_matrix;
    graph->nodes = create_nodes(num_nodes, adj_lists);
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
    decrease_key(queue, (void*) node, new_distance);
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
/*
node_type* getNode(graph_type* g, int key)
{
    for(int i = 0; i < g->num_nodes; i++)
    {
        if(g->nodes[i].key == key)
        { 
            return (g->nodes + i);
        }
    }
    return NULL;
}
*/

int order_node(const void* node_a, const void* node_b)
{
    return leq_int((void *) &(((node_type*) node_a)->distance_from_source), (void *) &(((node_type*) node_b)->distance_from_source));
}


void dijkstra_minheap(graph_type* g, node_type* source)
{
    initialise(g);
    source->distance_from_source = 0;
    binheap_type* queue = build_heap((void*) g->nodes, g->num_nodes, g->num_nodes-1, sizeof(unsigned int), order_node);

    while (!is_heap_empty(queue))
    {
        node_type* u = extract_min(queue);
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
    
    before_min->next = min->next;
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
    free(queue);
}

void delete_node(node_type* node)
{
    free(node->adjacents);
    free(node);
}
void delete_graph(graph_type* g)
{
    for (size_t i = 0; i < g->nodes; i++)
    {
        delete_node(g->nodes + i*sizeof(node_type));
    }
    free(g);
}
