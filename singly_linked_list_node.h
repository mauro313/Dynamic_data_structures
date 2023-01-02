#ifndef SINGLY_LINKED_LIST_NODE_H_INCLUDED
#define SINGLY_LINKED_LIST_NODE_H_INCLUDED
#include <stdbool.h>
#define t_elem int

typedef struct _sll_node{
 t_elem value;
 struct _sll_node* next;
}sll_node_t;

sll_node_t* sll_node_new(t_elem value);

void sll_node_free(sll_node_t** node);

t_elem sll_node_get_value(sll_node_t* node);

bool sll_node_nextisnull(sll_node_t* node);

sll_node_t* sll_node_get_next(sll_node_t* node);

sll_node_t** sll_node_get_next_referece(sll_node_t* node);

int sll_node_link_node(sll_node_t** origin,sll_node_t* destiny);

void sll_node_add_node_end_iterative(sll_node_t** head,sll_node_t* new_node);

void sll_node_add_node_end_recursive(sll_node_t** head,sll_node_t* new_node);

void sll_node_add_value_end(sll_node_t** head,t_elem value);

void sll_node_add_value_first(sll_node_t** sll_node,t_elem value);

void sll_node_printf(sll_node_t* node,void (*print)(t_elem));

void sll_node_all_printf_iterative(sll_node_t* head,void (*print)(t_elem));

void sll_node_all_printf_recursive(sll_node_t* head,void (*print)(t_elem));

sll_node_t** sll_node_search_recursive(sll_node_t** head,t_elem value,int (*compare)(t_elem,t_elem));

sll_node_t** sll_node_search_iterative(sll_node_t** head,t_elem value,int (*compare)(t_elem,t_elem));

sll_node_t* sll_node_remove(sll_node_t** head,t_elem value,int (*compare)(t_elem,t_elem));

#include "singly_linked_list_node.c"
#endif // SINGLE LINKED LIST NODE_H_INCLUDED
