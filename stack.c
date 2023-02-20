#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/**
 * @brief create a new stack.
 * 
 * @param maxsize 
 * @return stack_t* 
 */
stack_t* stack_new(int maxsize){
  stack_t* new_stack = (stack_t*)malloc(sizeof(stack_t));
  if(new_stack==NULL){
    printf("memory cannot be reserved for a new stack");
    exit(EXIT_FAILURE);
  }
  new_stack->top = NULL;
  new_stack->count = 0;
  new_stack->maxsize = maxsize;
  return new_stack;
}

/**
 * @brief free the memory of a stack
 * 
 * @param stack 
 */
void stack_free(stack_t** stack){
  if(stack!=NULL && *stack!=NULL){
    (*stack)->top = NULL;
    free(*stack);
    *stack = NULL;
  }
}

/**
 * @brief return the current size of the stack.
 * 
 * @param stack 
 * @return int 
 */
int stack_getsize(stack_t* stack){
  if(stack == NULL){
    printf("\nstack pointer is NULL(1)\n");
    exit(EXIT_FAILURE);
  }
  return stack->count;
}

/**
 * @brief introdue an element in a stack. Return true if the element was pushed and false otherwise (stack full). 
 * 
 * @param stack 
 * @param elem 
 * @return bool 
 */
bool push(stack_t* stack, t_elem elem){
  if(stack == NULL){
    printf("\nstack pointer is NULL(2)\n");
    exit(EXIT_FAILURE);
  }
  bool returned = false;
  if(!stack_isfull(stack)){
    sll_node_t* new_node = sll_node_new(elem);
    sll_node_link_node(&new_node,stack->top);
    stack->top = new_node;
    stack->count++;
    returned = true;
  }
  return returned;
}

/**
 * @brief remove the top element from a stack.
 * 
 * @param stack 
 * @return t_elem 
 */
t_elem pop(stack_t* stack){
  if(stack == NULL){
    printf("\nstack pointer is NULL(3)\n");
    exit(EXIT_FAILURE);
  }
  if(stack_isempty(stack)){
    printf("\nstack is empty\n");
    exit(EXIT_FAILURE);
  }
  t_elem returned = sll_node_get_value(stack->top);
  sll_node_t* auxiliar = stack->top;
  stack->top = sll_node_get_next(stack->top);
  sll_node_free(&auxiliar);
  stack->count--;
  return returned;
}

/**
 * @brief allows to see the top element from a stack
 * 
 * @param stack 
 * @return t_elem 
 */
t_elem top(stack_t* stack){
  if(stack == NULL){
    printf("\nstack pointer is NULL(4)\n");
    exit(EXIT_FAILURE);
  }
  if(stack_isempty(stack)){
    printf("\nstack is empty\n");
    exit(EXIT_FAILURE);
  }
  return sll_node_get_value(stack->top);
}

/**
 * @brief return true if the stack is empty and false otherwise.
 * 
 * @param stack 
 * @return true 
 * @return false 
 */
bool stack_isempty(stack_t* stack){
  if(stack == NULL){
    printf("\nstack pointer is NULL(5)\n");
    exit(EXIT_FAILURE);
  }
  return (stack->count == 0);
}

/**
 * @brief return true if the stack is full and false otherwise.
 * 
 * @param stack 
 * @return true 
 * @return false 
 */
bool stack_isfull(stack_t* stack){
 if(stack == NULL){
    printf("\nstack pointer is NULL(6)\n");
    exit(EXIT_FAILURE);
  }
  return (stack->count == stack->maxsize);
}

/**
 * @brief print a stack.
 * 
 * @param stack 
 * @param printf_elem 
 */
void stack_printf(stack_t* stack,void (*printf_elem)(t_elem)){
  if(stack == NULL){
    printf("\nstack pointer is NULL(7)\n");
    return;
  }
  if(!stack_isempty(stack)){
    t_elem auxiliar = pop(stack);
    printf_elem(auxiliar);
    stack_printf(stack,printf_elem);
    push(stack,auxiliar);
  }
}

/**
 * @brief traverse a stack using a context variable.
 * 
 * @param stack 
 * @param stack_do 
 * @param context 
 */
void stack_traverse(stack_t* stack,bool stack_do(t_elem,void*),void* context){
  if(stack == NULL){
    printf("\nstack pointer is NULL(8)\n");
    return;
  }
  if(!stack_isempty(stack) && stack_do(top(stack),context)){
    t_elem auxiliar = pop(stack);
    stack_traverse(stack,stack_do,context);
    push(stack,auxiliar);
  }
}
