#include <stdlib.h>
#include <stdlib.h>
#include "list.h"

/**
 * @brief create a new list
 * 
 * @param maxsize 
 * @return list_t* 
 */
list_t* list_new(int maxsize){
  list_t* list = (list_t*) malloc(sizeof(list_t));
  if(list==NULL){
    printf("\nmemory cannot be reserved for a list pointer\n");
    exit(EXIT_FAILURE);
  }
  list->head = NULL;
  list->maxsize = maxsize;
  list->count = 0;
  return list;
}

/**
 * @brief procedure to free the memory used in a list.
 * 
 * @param list 
 */
void list_free(list_t** list){
  if(list != NULL && *list != NULL){
    (*list)->head = NULL;
    free(*list);
    *list = NULL;
  }
}

/**
 * @brief return true if the list is empty and false otherwise.
 * 
 * @param list 
 * @return true 
 * @return false 
 */
bool list_isempty(list_t* list){
  if(list == NULL){
    printf("\nlist pointer is NULL(1)\n");
    exit(EXIT_FAILURE);
  }
  return (list->count == 0);
}

/**
 * @brief return true if the list is full and false otherwise.
 * 
 * @param list 
 * @return true 
 * @return false 
 */
bool list_isfull(list_t* list){
  if(list == NULL){
    printf("\nlist pointer is NULL(2)\n");
    exit(EXIT_FAILURE);
  }
  return (list->count == list->maxsize);
}

/**
 * @brief function that calculates the current size of a list.
 * 
 * @param list 
 * @return int 
 */
int list_length(list_t* list){
  if(list == NULL){
    printf("\nlist pointer is NULL(3)\n");
    exit(EXIT_FAILURE);
  }
  return list->count;
}

/**
 * @brief insert an element in a specific position.Return true if the element was inserted and false otherwise(list full).
 * 
 * @param list 
 * @param index 
 * @param elem 
 * @return bool 
 */
bool list_insert(list_t* list, int index, t_elem elem){
  if(list == NULL){
    printf("\nlist pointer is NULL(4)\n");
    exit(EXIT_FAILURE);
  }
  if(index<0 || index>list->count){
    printf("\ninvalid index(1)\n");
    exit(EXIT_FAILURE);
  }
  bool returned = false;
  if(!list_isfull(list)){
    sll_node_t* new_node = sll_node_new(elem);
    sll_node_t** auxiliar = &list->head;
    int counter = 0;
    while(counter < index){
      auxiliar = sll_node_get_next_referece(*auxiliar);
      counter++;
    }
    sll_node_link_node(&new_node,*auxiliar);
    *auxiliar = new_node;
    list->count++;
    returned = true;
  }
  return returned;
}

/**
 * @brief get the element of the specified position.
 * 
 * @param list 
 * @param index 
 * @return t_elem 
 */
t_elem list_get(list_t* list, int index){
  if(list == NULL){
    printf("\nlist pointer is NULL(5)\n");
    exit(EXIT_FAILURE);
  }
  if(index<0 || index>=list->count){
    printf("\ninvalid index(2)\n");
    exit(EXIT_FAILURE);
  }
  sll_node_t* auxiliar = list->head;
  int count = 0;
  while(count < index){
    auxiliar = sll_node_get_next(auxiliar);
    count++;
  }
  return  sll_node_get_value(auxiliar);
}

/**
 * @brief search an element in a list of linked nodes.Return the index of the element if exist and the
 * maxsize otherwise.
 * 
 * @param list 
 * @param elem 
 * @param compare 
 * @return int 
 */
int list_search(list_t* list, t_elem elem, int (*compare)(t_elem,t_elem)){
  if(list == NULL){
    printf("\nlist pointer is NULL(6)\n");
    exit(EXIT_FAILURE);
  }
  int returned = 0;
  sll_node_t* auxiliar = list->head;
  while(auxiliar!=NULL && compare(sll_node_get_value(auxiliar),elem)!=0){
    auxiliar = sll_node_get_next(auxiliar);
    returned++;
  }
  return returned;
}

/**
 * @brief delete the element of the list in the selected position.
 * 
 * @param list 
 * @param index 
 */
void list_delete(list_t* list, int index){
  if(list == NULL){
    printf("\nlist pointer is NULL(7)\n");
    return;
  }
  if(index<0 || index>=list->count){
    printf("\ninvalid index(3)\n");
    return;
  }
  int counter = 0;
  sll_node_t* remove = NULL;
  sll_node_t* auxiliar = list->head;
  sll_node_t* prev = NULL;
  while(counter < index){
    prev = auxiliar;
    auxiliar = sll_node_get_next(auxiliar);
    counter++;
  }
  remove = auxiliar;
  if(prev == NULL){
    list->head = sll_node_get_next(auxiliar);
  }
  else{
    sll_node_link_node(&prev,sll_node_get_next(auxiliar));
  }
  sll_node_free(&remove);
  list->count--;
}

/**
 * @brief traverse the list using a context variable.
 * 
 * @param list 
 * @param look 
 * @param ctx 
 */
void list_traverse(list_t *list, bool look(t_elem elem, int index, void *ctx), void *ctx){
  if(list == NULL){
    printf("\nlist pointer is NULL(8)\n");
    return;
  }
  sll_node_t* node = list->head;
  int index = 0;
  while (sll_node_get_next(node)!=NULL && look(sll_node_get_value(node), index, ctx)) {
    node = sll_node_get_next(node);
    index++;
  }
}
