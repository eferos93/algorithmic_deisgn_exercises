#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <limits.h>
#include <binheap.h>
#include <linked_list.h>

typedef struct Graph
{
    int num_nodes;
    //unsigned int* weights_matrix; //adj matrix
    node_type* nodes;
} graph_type;


typedef struct Node
{
    int key;
    //size_t key_size;
    list_node* adjacents;
    int distance_from_source;
    unsigned int position; //position inside the heap
    node_type* predecessor;
} node_type;
/*
typedef struct Adjacents
{
    unsigned int length;
    node_type** adj;
} adjacents_type;
*/
int order_node(const void * node_a, const void* node_b);

struct Node* create_node(int key);

graph_type* create_graph(unsigned int *adj_matrix, unsigned int num_nodes);

void dijkstra(graph_type* g, node_type* source);

#endif