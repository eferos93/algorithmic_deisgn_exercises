#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdlib.h>

typedef struct List_Node
{
    void* element;
    unsigned int weight;
    list_node* next;
} list_node;


typedef struct List
{
    list_node* head;
    size_t elem_size;
    size_t length;
} linked_list;

list_node* create_linked_list_node(void* element, size_t elem_size, unsigned int weight);
linked_list* create_linked_list(void* element, size_t elem_size, unsigned int weight);
void insert_new_node(linked_list* list, void* element, unsigned int weight);
void delete_linked_list_node(linked_list* list, void* element);
void delete_linked_list(linked_list* list);
void print_list(linked_list* list, void (*key_printer)(const void *value));
int in_list(linked_list* list_node, void* element);
#endif