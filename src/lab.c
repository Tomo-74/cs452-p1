#include "lab.h"

// These two need to be in main.c? They're for a specific integer implementation
void destroy_data(void *data)
{
    free(data);
}

int compare_to(const void* a, const void* b)
{
    return !(*(int*)a == *(int*)b);
}

list_t* list_init(void (*destroy_data)(void*), int (*compare_to)(const void*, const void*))
{
    list_t* list = (list_t*)malloc(sizeof(*list));
    list->destroy_data = destroy_data;
    list->compare_to = compare_to;
    list->size = 0;
    list->head = NULL;
    return list;
}

void list_destroy(list_t** ptr)
{
    list_t* list = *ptr;
    node_t* cur = list->head->next; // Skip sentinel node
    while(cur->data != NULL) {
        list_remove_node(list, cur);
        cur = list->head->next;
    }
}

list_t* list_add(list_t* list, void* data)
{
    node_t* head = list->head;
    node_t* new = (node_t*)malloc(sizeof(*new));

    // Set references
    new->data = data;
    new->next = head;
    new->prev = head->prev;
    head->prev->next = new;
    head->prev = new;
    return list;
}

// TODO Add unit tests for this functions
void* list_remove_node(list_t* list, node_t* node)
{
    // Update references
    node->prev->next = node->next;
    node->next->prev = node->prev;

    // Deallocate memory
    void* removedData = node->data;
    list->destroy_data(node->data);
    free(node->next); // unnecessary because next and prev are never malloc'd?
    free(node->prev);
    free(node);
    return removedData;
}

void* list_remove_index(list_t* list, size_t index)
{
    // Traverse to the node to remove
    node_t* cur = list->head->next;
    for(size_t i=0; i<index; i++) {
        cur = cur->next;
    }
    // Update references
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    // Deallocate memory
    void* removedData = cur->data;
    list->destroy_data(cur->data);
    free(cur->next);
    free(cur->prev);
    free(cur);
    return removedData;
}

int list_indexof(list_t* list, void* data)
{
    int index = 0;

    // Traverse list and compare nodes
    node_t* cur = list->head->next;
    while(cur->data != NULL && list->compare_to(cur->data, data)) {
        index++;
        cur = cur->next;
    }
    if(cur->data == NULL) return -1;
    return index;
}
