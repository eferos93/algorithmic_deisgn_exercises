#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Graph
{
    int num_nodes;
    unsigned int* weights_matrix; //adj matrix
    node_type* nodes;
} graph_type;

typedef struct Node
{
    int key;
    size_t key_size;
    int distance_from_source;
    //int position;
    node_type* predecessor;
} node_type;

typedef struct Adjacents
{
    unsigned int length;
    node_type** adj;
} adjacents_type;

struct Node* create_node(void* key, size_t key_size);

struct Graph* create_graph(unsigned int* adj_matrix, node_type* nodes, unsigned int num_nodes, size_t key_size);

void dijkstra();

#endif