#include "lab.h"

list_t* list_init(void (*destroy_data)(void*), int (*compare_to)(const void*, const void*))
{
    // Create empty list
    list_t* list = (list_t*)malloc(sizeof(list_t)); // updated sizeof param
    list->destroy_data = destroy_data;
    list->compare_to = compare_to;
    list->size = 0;

    // Link sentinel node
    node_t* head = (node_t*)malloc(sizeof(node_t)); // updated sizeof param
    head->data = NULL; // removed redundant dereferences
    head->next = head;
    head->prev = head;
    list->head = head;

    return list;
}

void list_destroy(list_t** plist)
{
    if(!plist) return; // added null check

    list_t* list = *plist;
    node_t* cur = list->head->next;

    // Destroy all user-added nodes
    while(list->size > 0) // updated the deletion operation
    {
        list->destroy_data(cur->data);
        cur = cur->next;
        free(cur->prev);
        list->size--;
    }

    // Free sentinel and list
    free(list->head);
    free(*plist);
    *plist = NULL;
}

list_t* list_add(list_t* list, void* data)
{
    if(!list) return NULL; // added param check
    if(!data) return list;

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
    if(!list || index >= list->size) return NULL; // added null check

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
    if(!list) return -1; // added null check

    int index = 0;

    // Traverse list and compare nodes
    node_t* cur = list->head->next;
    while(cur != list->head) {
        if(list->compare_to(cur->data, data) == 0) return index; // updated if statement condition
        index++;
        cur = cur->next;
    }

    return -1;
}
