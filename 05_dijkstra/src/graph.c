#include <graph.h>
#include <limits.h>
#include <binheap.h>

node_type *create_nodes(unsigned int num_of_nodes)
{
    node_type *new_nodes = (node_type *)malloc(sizeof(node_type)*num_of_nodes);
    for (size_t i = 0; i < num_of_nodes; i++)
    {
        new_nodes[i].key = i;
        new_nodes[i].distance_from_source = UINT_MAX;
        new_nodes[i].predecessor = NULL;
    }
    
    //new_node->key = key;
    //new_node->key_size = key_size;
    //new_node->distance_from_source = UINT_MAX;
    //new_node->predecessor = NULL;

    return new_nodes;
}



unsigned int weight(graph_type *g, node_type *from, node_type *to)
{
    return g->weights_matrix[from->key * g->num_nodes + to->key];
}

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

graph_type *create_graph(unsigned int *adj_matrix, unsigned int num_nodes)
{
    graph_type *graph = (graph_type *)malloc(sizeof(graph_type));
    graph->num_nodes = num_nodes;
    graph->weights_matrix = adj_matrix;
    graph->nodes = create_nodes(num_nodes);
    return graph;
}

void initialise(graph_type *g)
{
    for (int i = 0; i < g->num_nodes; i++)
    {
        //(g->nodes[i]).key = i;
        g->nodes[i].distance_from_source = UINT_MAX;
        g->nodes[i].predecessor = NULL;
    }
}

void update_distance(binheap_type *queue, node_type *node, unsigned int new_distance)
{
    decrease_key(queue, node->position, new_distance);
}

void relax(binheap_type *queue, node_type *u, node_type *v, unsigned int weight)
{
    if (u->distance_from_source + weight < v->distance_from_source)
    {
        update_distance(queue, v, u->distance_from_source + weight);
        v->predecessor = u;
    }
}

void relax(node_type *u, node_type *v, unsigned int weight)
{
    if (u->distance_from_source + weight < v->distance_from_source)
    {
        v->distance_from_source = u->distance_from_source + weight;
        v->predecessor = u;
    }
}

node_type* getNode(graph_type* g, int key)
{
    for(int i = 0; i < g->num_nodes; i++)
    {
        if(g->nodes[i].key == key){ 
            return (g->nodes + i);
        }
    }
    return NULL;
}

void dijkstra(graph_type* g, node_type* source)
{
    initialise(g);
    source->distance_from_source = 0;
    //binheap_type* queue = build_heap(g->nodes);
}