#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <limits.h>
#include <binheap.h>
#include <linked_list.h>

typedef struct Node
{
    int key;
    size_t distance_from_source;
    linked_list* adjacents;
    struct Node* predecessor;
} node_type;

typedef struct Graph
{
    size_t num_nodes;
    //adj matrix
    node_type* nodes;
} graph_type;

int order_node(const void * node_a, const void* node_b);

node_type create_node(int key);
node_type *create_nodes(size_t num_of_nodes, int* keys);
graph_type* create_graph(size_t num_of_nodes, int* keys);
void dijkstra_minheap(graph_type* g, node_type* source);
void dijkstra_array(graph_type* g, node_type* source);
void delete_graph(graph_type* g);
void delete_node(node_type* node);
void print_graph(graph_type* g, void (*key_printer)(const void *value));

#endif