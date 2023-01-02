#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include "singly_linked_list_node.h"

typedef struct{
  sll_node_t* head;
  sll_node_t* tail;
  int maxsize;
  int count;
}queue_t;

queue_t* queue_new(int maxsize);

void queue_free(queue_t** queue);

int queue_getsize(queue_t* queue); 

int queue_getmaxsize(queue_t* queue); 

bool queue_isfull(queue_t* queue); 

bool queue_isempty (queue_t* queue); 

int enqueue(queue_t* queue, t_elem elem); 

void queue_printf(queue_t* queue,void (*printf_elem)(t_elem));

t_elem dequeue(queue_t* queue); 

t_elem peek(queue_t* queue); 

void queue_traverse(queue_t* queue,bool queue_do(t_elem,void*),void* context);

#include "queue.c"
#endif //QUEUE_H_INCLUDED