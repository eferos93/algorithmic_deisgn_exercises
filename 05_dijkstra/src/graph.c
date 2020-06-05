#include <graph.h>
#include <limits.h>
#include <binheap.h>

node_type* create_node(void* key, size_t key_size)
{
    node_type* new_node = (node_type*) malloc(sizeof(node_type));
    new_node->key = key;
    new_node->key_size = key_size;
    new_node->distance_from_source = UINT_MAX;
    new_node->predecessor = NULL;

    return new_node;
}

unsigned int weight(graph_type* g, node_type* from, node_type* to)
{
    return g->weights_matrix[ from->key*g->num_nodes + to->key ];
}


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

// returns nodes adjacent to a given node
adjacents_type adjacents(graph_type* g, node_type* node, int n)
{
    node_type** adj_nodes = (node_type**) malloc(sizeof(node_type*)*n);
    int adj_index = 0;
    for(int i = 0; i < g->num_nodes; i++)
    {
        int weight_node_to_i = weight(g, node, &(g->nodes)[i]);
        if(weight_node_to_i < UINT_MAX && (g->nodes)[i].key != node->key)
        {
            adj_nodes[adj_index++] = &(g->nodes)[i];
        }
            
    }
    adjacents_type adj;
    adj.adj = adj_nodes;
    adj.length = adj_index;
    return adj;
}

graph_type* create_graph(unsigned int* adj_matrix, node_type* nodes, unsigned int num_nodes, size_t key_size)
{
    graph_type* graph = (graph_type*) malloc(sizeof(graph_type));
    graph->num_nodes = num_nodes;
    graph->weights_matrix = adj_matrix;
    graph->nodes = nodes;
    return graph;
}

void initialise(graph_type* g) 
{
    int n = g->num_nodes;
    for(int i = 0; i < n; i++)
    {
        (g->nodes[i]).key = i;
        (g->nodes[i]).distance_from_source = UINT_MAX;
        (g->nodes[i]).predecessor = NULL;
    }
}

void relax(binheap_type* q, node_type* u, node_type* v, int w)
{
    if(u->distance_from_source + w < v->distance_from_source)
    {
        update_distance(q, v, u->distance_from_source + w);
        v->predecessor = u;
    }
}