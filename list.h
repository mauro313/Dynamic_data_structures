#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include "singly_linked_list_node.h" 

typedef struct{
  sll_node_t* head;
  int maxsize;
  int count;
}list_t;

list_t* list_new(int maxsize);

void list_free(list_t** list);

bool list_isempty(list_t* list);

bool list_isfull(list_t* list);

int list_length(list_t* list);

int list_insert(list_t* list, int index, t_elem elem);

t_elem list_get(list_t* list, int index);

int list_search(list_t* list, t_elem elem, int (*compare)(t_elem,t_elem));

void list_delete(list_t* list, int index);

void list_traverse(list_t *L, bool look(t_elem elem, int index, void *ctx), void *ctx);

#include "list.c"
#endif //LIST_H_INCLUDED