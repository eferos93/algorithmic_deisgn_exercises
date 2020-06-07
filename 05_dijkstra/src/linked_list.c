#include <linked_list.h>
#include <stdio.h>

list_node* create_linked_list_node(void* element, unsigned int weight)
{
    list_node* new_node = (list_node*) malloc(sizeof(list_node));
    new_node->next = NULL;
    new_node->element = element;//malloc(elem_size);
    new_node->weight = weight;
    return new_node;
}

linked_list* create_linked_list(void* element, size_t elem_size, unsigned int weight)
{
    linked_list* new_list = (linked_list*) malloc(sizeof(linked_list));
    new_list->elem_size = elem_size;
    new_list->head = create_linked_list_node(element, weight);
    new_list->length = 1;
    return new_list;
}

void insert_new_node(linked_list* list, void* element, unsigned int weight)
{
    list_node* new_node = create_linked_list_node(element, weight);
    new_node->next = list->head;
    list->head = new_node;
    list->length++;
}

void delete_linked_list_node(linked_list* list, void* element)
{
    list_node* current = list->head;
    list_node* previous = NULL;
    while (current->element != element && current)
    {
        previous = current;
        current = current->next;
    }

    if (current)
    {
        previous->next = current->next;
        current->next = NULL;
        //free(current->element);
        free(current);
    }
}

void delete_linked_list(linked_list* list)
{
    list_node* current = list->head;
    list_node* next = NULL;
    while (current)
    {
        next = current->next;
        //free(current->element);
        free(current);
        current = next;
    }
    free(list);
}

void print_list(linked_list* list, void (*key_printer)(const void *value))
{
    list_node* current = list->head;
    while (current)
    {
        printf("->(key: ");
        key_printer(current->element);
        printf(", w: %u)", current->weight);
        current = current->next;
    }
    
}

int in_list(linked_list* list, void* element)
{
    list_node* current = list->head;
    while (current)
    {
        if (current->element == element)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}