#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// funcion para crear un nuevo stack 
stack_t* stack_new(int maxsize){
  stack_t* new_stack = (stack_t*)malloc(sizeof(stack_t));
  if(new_stack==NULL){
    printf("memeory cannot be reserved for a new stack");
    exit(-1);   
  } 
  new_stack->top = NULL;
  new_stack->count = 0;
  new_stack->maxsize = maxsize;
  return new_stack;   
}

//Procedimiento para liberar la memeria de un stack
void stack_free(stack_t** stack){
  if(stack!=NULL && *stack!=NULL){
    (*stack)->top = NULL;
    free(*stack);
    *stack = NULL;  
  }    
}

//Funcion que retorna el tamaño del stack
int stack_getsize(stack_t* stack){
  if(stack == NULL){
    printf("stack pointer is NULL");
    exit(-2);  
  }
  return stack->count;    
}

//Procedimiento para añadir un elemento al stack.Retorna 1 cuando se agrego el valor y 0 en caso contrario(stack lleno).
int push(stack_t* stack, t_elem elem){
  if(stack == NULL){
    printf("stack pointer is NULL");
    exit(-3);  
  } 
  int returned = 0;
  if(!stack_isfull(stack)){
    sll_node_t* new_node = sll_node_new(elem); 
    sll_node_link_node(&new_node,stack->top);
    stack->top = new_node;
    stack->count++;  
    returned = 1;
  }
  return returned;
}

//Funcion para remover un elemento del stack 
t_elem pop(stack_t* stack){
  if(stack == NULL){
    printf("stack pointer is NULL");
    exit(-4);  
  }
  if(stack_isempty(stack)){
    printf("stack is empty");
    exit(-5);    
  }    
  t_elem returned = sll_node_get_value(stack->top);
  sll_node_t* auxiliar = stack->top;
  stack->top = sll_node_get_next(stack->top);
  sll_node_free(&auxiliar);
  stack->count--;
  return returned;
}

//Funcion para conocer el elemento del tope del stack
t_elem top(stack_t* stack){
  if(stack == NULL){
    printf("stack pointer is NULL");
    exit(-6);  
  }
  if(stack_isempty(stack)){
    printf("stack is empty");
    exit(-7);    
  } 
  return sll_node_get_value(stack->top);     
}

//Funcion que retorna 1 si el stack esta vacio y cero si no lo esta
bool stack_isempty(stack_t* stack){
  if(stack == NULL){
    printf("stack pointer is NULL");
    exit(-8);  
  }
  bool retuned = false;
  if(stack->count == 0){
    retuned = true;  
  } 
  return retuned; 
}

//Funcion que retorna 1 si el stack esta lleno y cero si no lo esta
bool stack_isfull(stack_t* stack){
  if(stack == NULL){
    printf("stack pointer is NULL");
    exit(-9);  
  }
  bool retuned = false;
  if(stack->count == stack->maxsize){
    retuned = true;  
  } 
  return retuned; 
}

//Procedimiento para imprimir el contenido de un stack
void stack_printf(stack_t* stack,void (*printf_elem)(t_elem)){
  if(stack == NULL){
    printf("stack pointer is NULL");
    exit(-10);
  }
  if(!stack_isempty(stack)){
    t_elem auxiliar = pop(stack);
    printf_elem(auxiliar);
    stack_printf(stack,printf_elem);
    push(stack,auxiliar);        
  }        
}

//Procedimento para recorrer el stack usando una variable de contexto.
void stack_traverse(stack_t* stack,bool stack_do(t_elem,void*),void* context){
  if(stack == NULL){
    printf("stack pointer is NULL");
    exit(-11);  
  }
  if(!stack_isempty(stack) && stack_do(top(stack),context)){
    t_elem auxiliar = pop(stack);
    stack_traverse(stack,stack_do,context);
    push(stack,auxiliar);  
  }      
}