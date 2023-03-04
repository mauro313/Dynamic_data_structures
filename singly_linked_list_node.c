#include <stdlib.h>
#include <stdio.h>
#include "singly_linked_list_node.h"

/**
 * @brief creation of a new node.
 *
 * @param value
 * @return sll_node_t*
 */
sll_node_t* sll_node_new(t_elem value){
  sll_node_t* new_node = (sll_node_t*)malloc(sizeof(sll_node_t));
  if(new_node == NULL){
    printf("\nmemory cannot be reserved for a new sll_node\n");
    exit(EXIT_FAILURE);
  }
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

/**
 * @brief free the memory of a node.
 *
 * @param node
 */
void sll_node_free(sll_node_t** node){
  if(node != NULL && *node!=NULL){
    (*node)->next = NULL;
    free(*node);
    *node = NULL;
  }
}

/**
 * @brief return the element of a node.
 *
 * @param node
 * @return t_elem
 */
t_elem sll_node_get_value(sll_node_t* node){
  if(node == NULL){
    printf("\nsll_node pointer is NULL(1)\n");
    exit(EXIT_FAILURE);
  }
  return node->value;
}

/**
 * @brief set the element of a node.
 *
 * @param node
 * @param value
 */
void sll_node_set_value(sll_node_t** node,t_elem value){
  if(node == NULL){
    printf("\nsll_node pointer is NULL(2)\n");
    return;
  }
  (*node)->value = value;
}

/**
 * @brief return true if the next of a node is null and false otherwise.
 *
 * @param node
 * @return true
 * @return false
 */
bool sll_node_nextisnull(sll_node_t* node){
  if(node == NULL){
    printf("\nsll_node pointer is NULL(3)\n");
    exit(EXIT_FAILURE);
  }
  bool returned = false;
  if(node->next == NULL){
    returned =true;
  }
  return returned;
}

/**
 * @brief return the next of a node.
 *
 * @param node
 * @return sll_node_t*
 */
sll_node_t* sll_node_get_next(sll_node_t* node){
  if(node == NULL){
    printf("\nsll_node pointer is NULL(4)\n");
    exit(EXIT_FAILURE);
  }
  return node->next;
}

/**
 * @brief return the next refernce of a node.
 *
 * @param node
 * @return sll_node_t**
 */
sll_node_t** sll_node_get_next_referece(sll_node_t* node){
  if(node == NULL){
    printf("\nsll_node pointer is NULL(5)\n");
    exit(EXIT_FAILURE);
  }
  return &node->next;
}

/**
 * @brief link two nodes.Return true if *origin is not null and false otherwise.
 *
 * @param origin
 * @param destiny
 * @return bool
 */
bool sll_node_link_node(sll_node_t** origin,sll_node_t* destiny){
  if(origin == NULL){
    printf("\nsll_node double pointer is NULL(1)\n");
    exit(EXIT_FAILURE);
  }
  bool returned = false;
  if(*origin != NULL){
    (*origin)->next = destiny;
    returned = true;
  }
  return returned;
}

/**
 * @brief add a node at the end of a list of linked nodes.Iterative version.
 *
 * @param head
 * @param new_node
 */
void sll_node_add_node_end_iterative(sll_node_t** head,sll_node_t* new_node){
  if(head == NULL){
    printf("\nsll_node double pointer is NULL(2)\n");
    return;
  }
  if(*head == NULL){
    *head = new_node;
  }
  else{
    sll_node_t* aux = *head;
    while(aux->next!=NULL){
      aux = aux->next;
    }
    aux->next = new_node;
  }
}

/**
 * @brief add a node at the end of a list of linked nodes.Recursive version.
 *
 * @param head
 * @param new_node
 */
void sll_node_add_node_end_recursive(sll_node_t** head,sll_node_t* new_node){
  if(head == NULL){
    printf("\nsll_node double pointer is NULL(3)\n");
    return;
  }
  if(*head == NULL){
    *head = new_node;
  }
  else{
    sll_node_add_node_end_recursive(&(*head)->next,new_node);
  }
}

/**
 * @brief add an element at the end of a list of linked nodes.
 *
 * @param head
 * @param value
 */
void sll_node_add_value_end(sll_node_t** head,t_elem value){
  if(head == NULL){
    printf("\nsll_node double pointer is NULL(4)\n");
    return;
  }
  sll_node_t* new_node = sll_node_new(value);
  sll_node_add_node_end_iterative(head,new_node);
}

/**
 * @brief add an element at the begin of a list of linked nodes.
 *
 * @param head
 * @param value
 */
void sll_node_add_value_first(sll_node_t** head,t_elem value){
  if(head == NULL){
    printf("\nsll_node double pointer is NULL(5)\n");
    return;
  }
  sll_node_t* new_node = sll_node_new(value);
  new_node->next = *head;
  *head = new_node;
}

/**
 * @brief print a node.
 *
 * @param node
 * @param print
 */
void sll_node_printf(sll_node_t* node,void (*print)(t_elem)){
  if(node == NULL){
    printf("\nsll_node pointer is NULL(6)\n");
    return;
  }
  print(node->value);
}

/**
 * @brief print a list of linked nodes.Iterative version.
 *
 * @param head
 * @param print
 */
void sll_node_all_printf_iterative(sll_node_t* head,void (*print)(t_elem)){
  if(head == NULL){
    printf("\nsll_node pointer is NULL(7)\n");
    return;
  }
  sll_node_t* auxiliar = head;
  while(auxiliar!=NULL){
    print(auxiliar->value);
    auxiliar = auxiliar->next;
  }
}

/**
 * @brief print a list of linked nodes.Recursive version.
 *
 * @param head
 * @param print
 */
void sll_node_all_printf_recursive(sll_node_t* head,void (*print)(t_elem)){
  if(head == NULL){
    printf("\nsll_node pointer is NULL(8)\n");
    return;
  }
  else{
    print(head->value);
    if(head->next != NULL){
      sll_node_all_printf_recursive(head->next,print);
    }
  }
}

/**
 * @brief search an element in a list of a linked nodes.Return the reference of the node if it exist.
 * Recursive version.
 *
 * @param head
 * @param value
 * @param compare
 * @return sll_node_t**
 */
sll_node_t** sll_node_search_recursive(sll_node_t** head,t_elem value,int(*compare)(t_elem,t_elem)){
  if(head == NULL){
    printf("\nsll_node double pointer is NULL(6)\n");
    exit(EXIT_FAILURE);
  }
  sll_node_t** auxiliar = NULL;
  if(*head!=NULL && compare(sll_node_get_value(*head),value)!=0){
    auxiliar = sll_node_search_recursive(&(*head)->next,value,compare);
  }
  else{
    auxiliar = head;
    if(*auxiliar == NULL){
      auxiliar = NULL;
    }
  }
  return auxiliar;
}

/**
 * @brief search an element in a list of a linked nodes.Return the reference of the node if it exist.
 * Iterative version.
 *
 * @param head
 * @param value
 * @param compare
 * @return sll_node_t**
 */
sll_node_t** sll_node_search_iterative(sll_node_t** head,t_elem value,int (*compare)(t_elem,t_elem)){
  if(head == NULL){
    printf("\nsll_node double pointer is NULL(7)\n");
    exit(EXIT_FAILURE);
  }
  sll_node_t** auxiliar = head;
  while((*auxiliar)!=NULL && compare((*auxiliar)->value,value)!=0){
    auxiliar = &(*auxiliar)->next;
  }
  if(*auxiliar == NULL){
    auxiliar == NULL;
  }
  return auxiliar;
}

/**
 * @brief remove an element of a list of linked nodes.Return the node that contains the searched element.
 *
 * @param head
 * @param value
 * @param compare
 * @return sll_node_t*
 */
sll_node_t* sll_node_remove(sll_node_t** head,t_elem value,int (*compare)(t_elem,t_elem)){
  if(head == NULL){
    printf("\nsll_node double pointer is NULL(8)\n");
    exit(EXIT_FAILURE);
  }
  sll_node_t* node_to_remove =NULL;
  sll_node_t* auxiliar = *head;
  sll_node_t* prev = NULL;
  while((auxiliar!= NULL) && (compare(auxiliar->value,value)!=0)){
    prev=auxiliar;
    auxiliar=auxiliar->next;
  }
  if(auxiliar!=NULL){
    node_to_remove = auxiliar;
    if(prev == *head){
      *head = auxiliar->next;
    }
    else{
      prev->next = auxiliar->next;
    }
    node_to_remove->next = NULL;
  }
  return auxiliar;
}



