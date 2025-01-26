#include "lab.h"

list_t* list_init(void (*destroy_data)(void*), int (*compare_to)(const void*, const void*))
{
    list_t* list = (list_t*)malloc(sizeof(*list));
    list->destroy_data = destroy_data;
    list->compare_to = compare_to;
    list->size = 0;

    // Link sentinel node
    node_t* head = (node_t*)malloc(sizeof(*head));
    list->head = head;
    list->head->data = NULL;
    list->head->next = head;
    list->head->prev = head;

    return list;
}

void list_destroy(list_t** ptr)
{
    list_t* list = *ptr;

    // Destroy all user-added nodes
    for(size_t i=0; i < list->size; i++) 
    {
        free(list_remove_index(list, i));
    }
    free(list->head); // Free sentinel
    free(list);
}

list_t* list_add(list_t* list, void* data)
{
    node_t* head = list->head;
    node_t* new = (node_t*)malloc(sizeof(*new));
    // Set references
    new->data = data;
    new->prev = head;
    new->next = head->next;
    head->next->prev = new;
    head->next = new;
    list->size++;
    return list;
}

void* list_remove_index(list_t* list, size_t index)
{
    if(index >= list->size) return NULL;

    // Find node to remove
    node_t* cur = list->head->next;
    for(size_t i=0; i<index; i++) {
        cur = cur->next;
    }
    void* data = cur->data;

    // Unlink node from list
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    
    free(cur);
    list->size--;
    return data;
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
