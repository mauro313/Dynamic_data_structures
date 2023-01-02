#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "singly_linked_list_node.h"

typedef struct{
  sll_node_t* top;
  int maxsize;
  int count;
}stack_t;
 
stack_t* stack_new(int maxsize);

void stack_free(stack_t** stack);

int stack_getsize(stack_t* stack);

int push(stack_t* stack, t_elem elem);

t_elem pop(stack_t* stack);

t_elem top(stack_t* stack);

bool stack_isempty(stack_t* stack);

bool stack_isfull(stack_t* stack);

void stack_printf(stack_t* stack,void (*printf_elem)(t_elem));

void stack_traverse(stack_t* stack,bool stack_do(t_elem,void*),void* context); 

#include "stack.c"
#endif //STACK_H_INCLUDED