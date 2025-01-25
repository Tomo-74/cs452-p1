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
    node_t* curNode = list->head->next; // start at second node (sentinel has no data to destroy)
    while(curNode->data != NULL) {
        list->destroy_data(curNode->data);
        curNode = curNode->next;
    }
}

list_t* list_add(list_t* list, void* data)
{
    node_t* head = list->head; // sentinel node
    node_t* newNode = (node_t*)malloc(sizeof(*newNode));
    newNode->data = data;
    newNode->next = head;
    newNode->prev = head->prev;
    head->prev->next = newNode;
    head->prev = newNode;
    return list;
}

// TODO
void* list_remove_index(list_t* list, size_t index)
{
    return 0;
}

// TODO
int list_indexof(list_t* list, void* data)
{
    return 0;
}
