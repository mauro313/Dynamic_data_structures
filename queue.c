#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/**
 * @brief create a new queue of the specified max size.
 * 
 * @param maxsize 
 * @return queue_t* 
 */
queue_t* queue_new (int maxsize){
  queue_t* new_queue = (queue_t*)malloc(sizeof(queue_t));
  if(new_queue==NULL){
    printf("\nmemory cannot be reserved for a new queue\n");
    exit(EXIT_FAILURE);
  }
  new_queue->head = NULL;
  new_queue->tail = NULL;
  new_queue->maxsize = maxsize;
  new_queue->count = 0;
  return new_queue;
}

/**
 * @brief free the memory of a stack
 * 
 * @param queue 
 */
void queue_free(queue_t** queue){
  if(queue!=NULL &&  *queue!=NULL){
    (*queue)->head = NULL;
    (*queue)->tail = NULL;
    free(*queue);
    *queue = NULL;
  }
}

/**
 * @brief get the current size of a queue.
 * 
 * @param queue 
 * @return int 
 */
int queue_getsize(queue_t* queue){
  if(queue == NULL){
    printf("\nqueue pointer is NULL(1)\n");
    exit(EXIT_FAILURE);
  }
  return queue->count;
}

/**
 * @brief return true if the queue is full and false otherwise.
 * 
 * @param queue 
 * @return true 
 * @return false 
 */
bool queue_isfull(queue_t* queue){
   if(queue == NULL){
    printf("\nqueue pointer is NULL(2)\n");
    exit(EXIT_FAILURE);
  }
  return (queue->count == queue->maxsize);
}

/**
 * @brief return true if the queue is empty and false otherwise.
 * 
 * @param queue 
 * @return true 
 * @return false 
 */
bool queue_isempty(queue_t* queue){
   if(queue == NULL){
    printf("\nqueue pointer is NULL(3)\n");
    exit(EXIT_FAILURE);
  }
  return (queue->count == 0);
}

/**
 * @brief introduce an element into a queue. Return true if the element was inserted and false otherwise.
 * 
 * @param queue 
 * @param elem 
 * @return bool 
 */
bool enqueue(queue_t* queue, t_elem elem){
   if(queue == NULL){
    printf("\nqueue pointer is NULL(4)\n");
    exit(EXIT_FAILURE);
  }
  bool returned = false;
  if(!queue_isfull(queue)){
    sll_node_t* new_node = sll_node_new(elem);
    if(queue_isempty(queue)){
      queue->head = new_node;
      queue->tail = new_node;
    }
    else{
      sll_node_link_node(&queue->tail,new_node);
      queue->tail = new_node;
    }
    queue->count++;
    returned = true;
  }
  return returned;
}

/**
 * @brief print a queue.
 * 
 * @param queue 
 * @param printf_elem 
 */
void queue_printf(queue_t* queue,void (*printf_elem)(t_elem)){
  if(queue == NULL){
    printf("\nqueue pointer is NULL(5)\n");
    return;
  }
  for(int i=0;i<queue->count;i++){
    t_elem auxiliar = dequeue(queue);
    printf_elem(auxiliar);
    enqueue(queue,auxiliar);
  }
}

/**
 * @brief remove an element from a queue.
 * 
 * @param queue 
 * @return t_elem 
 */
t_elem dequeue(queue_t* queue){
  if(queue == NULL){
    printf("\nqueue pointer is NULL(6)\n");
    exit(EXIT_FAILURE);
  }
  if(queue_isempty(queue)){
    printf("\nqueue is empty(1)\n");
    exit(EXIT_FAILURE);
  }
  t_elem returned = sll_node_get_value(queue->head);
  sll_node_t* deleted = queue->head;
  if(sll_node_get_next(queue->head) == NULL){
    queue->head = NULL;
    queue->tail = NULL;
  }
  else{
    queue->head = sll_node_get_next(queue->head);
  }
  sll_node_free(&deleted);
  queue->count--;
  return returned;
}

/**
 * @brief allows to see the peek element form a queue.
 * 
 * @param queue 
 * @return t_elem 
 */
t_elem peek(queue_t* queue){
   if(queue == NULL){
    printf("\nqueue pointer is NULL(7)\n");
    exit(EXIT_FAILURE);
  }
  if(queue_isempty(queue)){
    printf("\nqueue is empty(2)\n");
    exit(EXIT_FAILURE);
  }
  return sll_node_get_value(queue->head);
}

/**
 * @brief traverse a queue using a contex variable.
 * 
 * @param queue 
 * @param queue_do 
 * @param context 
 */
void queue_traverse(queue_t* queue,bool queue_do(t_elem,void*),void* context){
   if(queue == NULL){
    printf("\nqueue pointer is NULL(8)\n");
    return;
  }
  int size = queue_getsize(queue);
  int counter = 0;
  while(counter<size && queue_do(peek(queue),context)){
    t_elem auxiliar = dequeue(queue);
    enqueue(queue,auxiliar);
    counter++;
  }
  while(counter<size){
    enqueue(queue,dequeue(queue));
  }
}
