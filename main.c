#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "list.h"
#include "stack.h"
#include "queue.h"

void separate_list(list_t** list,queue_t* queue,stack_t* stack);
list_t* list_int(int maxsize);
void printf_int(t_elem value);
int compare_int(t_elem value1,t_elem value2);
bool look_andPrintf(t_elem value,int index,void* ctx);
bool look_andPrintfElement(t_elem value,void* context);
void queue_destroy(queue_t** queue);
void stack_destroy(stack_t** stack);

int main(void){
  //creo la lista de 20 enteros
  list_t* list = list_int(20);
  
  //creo el stack y la queue que van a ser utilizados para el procedimiento separate list
  stack_t* stack = stack_new(20);
  queue_t* queue = queue_new(20);

  //imprimo la lista de enteros
  list_traverse(list,look_andPrintf,NULL);
  printf("\n\n");

  //separo los enteros pares e impares en una queue y un stack
  separate_list(&list,queue,stack);

  //imprimo la queue
  queue_printf(queue,printf_int);
  printf("\n");
  queue_traverse(queue,look_andPrintfElement,NULL);
  printf("\n\n");

  //imprimo el stack
  stack_printf(stack,printf_int);
  printf("\n");
  stack_traverse(stack,look_andPrintfElement,NULL);

  //libero memoria del stack y la queue
  queue_destroy(&queue);
  stack_destroy(&stack);
  
  return 0;    
}

///******Ejemplo de la aplicacion de las 3 implementaciones*******///

//Procedimento para separar los elementos de una lista en un stack y una queue
//Los elemento pares se agrupan en la queue y los impares en el stack 
void separate_list(list_t** list,queue_t* queue,stack_t* stack){
  while(!list_isempty(*list)){
    t_elem auxiliar = list_get(*list,0);
    list_delete(*list,0);
    if(auxiliar%2 == 0){
      enqueue(queue,auxiliar);  
    }
    else{
      push(stack,auxiliar);  
    }
  }
  list_free(list);
}

//elimina una queue de enteros
void queue_destroy(queue_t** queue){
  while(!queue_isempty(*queue)){
    dequeue(*queue);  
  }
  queue_free(queue);  
}

//elimina un stack de enteros
void stack_destroy(stack_t** stack){
  while(!stack_isempty(*stack)){
    pop(*stack);  
  } 
  stack_free(stack); 
}

//crea una lista de enteros
list_t* list_int(int maxsize){
  list_t* new = list_new(maxsize);
  srand(time(NULL));
  while(!list_isfull(new)){
    list_insert(new,0,rand()%30);   
  }
  return new;    
}

//funcion auxiliar para list_traverse
bool look_andPrintf(t_elem value,int index,void* ctx){
  printf("%i ",value);
  return true;    
}

//funcion auxiliar para  queue_traverse y stack_traverse
bool look_andPrintfElement(t_elem value,void* context){
  printf("%d ",value);
  return true;
}


//procedimientos auxiliares
int compare_int(t_elem value1,t_elem value2){
  return value1-value2;  
}

void printf_int(t_elem value){
  printf("%i ",value);  
}
///////////////////////////