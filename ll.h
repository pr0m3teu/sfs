#ifndef LL_H_
#define LL_H_



typedef struct node_s {
    void* data;
    struct node_s* next;
} node_t;

typedef struct ll_s {
    node_t* head;
    node_t* tail;
    size_t data_size;

} ll_t;


int init_ll(ll_t* list, size_t data_size);
int insert_ll(ll_t* list, void* data);
int free_ll(ll_t *list);

#ifdef LL_IMPLEMENTATION

#include <stdlib.h>


int init_ll(ll_t* list, size_t data_size)
{
    if (list == NULL)
    {
        return -1;
    }

    list->head = (node_t*) malloc(sizeof(node_t));
    if (list->head == NULL) 
    {
        return -1;
    }
    list->tail = list->head;

    list->head->data = NULL;
    list->head->next = NULL;

    list->data_size = data_size;
    return data_size;
}


int insert_ll(ll_t* list, void* data)
{
    if (list == NULL || data == NULL || list->head == NULL) 
    {
        return -1;
    }

    if (list->head == list->tail && list->head->data == NULL)
    {
       list->head->data = malloc(list->data_size);
       if (list->head->data == NULL) return -1;
       memcpy(list->head->data, data, list->data_size);
       return 0;

    }

    node_t *node = (node_t*) malloc(sizeof(node_t));
    if (node == NULL) return -1;

    node->next = NULL;
    node->data = malloc(list->data_size);
    if (node->data == NULL) return -1;
    memcpy(node->data, data, list->data_size);

    tail->next = node;
    tail = node;

    return 0;
}


int free_ll(ll_t* list) {

    if (list == NULL) return -1;

    node_t *p = list->head->next;
    while(p != list->tail)
    {
        free(list->head->data);
        free(list->head);
        list->head = p;
        p = p->next;
    }

    free(p->data);
    free(p);

}

#endif // LL_IMPLEMENTATION

#endif // LL_H_
