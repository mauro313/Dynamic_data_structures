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
  //creation of a list of 20 int
  list_t* list = list_int(20);
  
  //creation of the stack and queue that will were used in separate_list
  stack_t* stack = stack_new(20);
  queue_t* queue = queue_new(20);

  //print the list.
  list_traverse(list,look_andPrintf,NULL);
  printf("\n\n");

  //separo los enteros pares e impares en una queue y un stack
  //separate the even and odd elements in the queue and stack
  separate_list(&list,queue,stack);

  //print the queue
  queue_traverse(queue,look_andPrintfElement,NULL);
  printf("\n\n");

  //print the stack
  stack_traverse(stack,look_andPrintfElement,NULL);

  //free the used memory.
  queue_destroy(&queue);
  stack_destroy(&stack);
  
  list_free(&list);

  return 0;    
}

///******Examples of application of the tree implementations.*******///

//Procedimento para separar los elementos de una lista en un stack y una queue
//Los elemento pares se agrupan en la queue y los impares en el stack 
/**
 * @brief procedure that separates the elements of a list in a stack and in a queue.
 * In the queue will going the even elements and in the stack the odds.
 * 
 * @param list 
 * @param queue 
 * @param stack 
 */
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

/**
 * @brief delete a int queue.
 * 
 * @param queue 
 */
void queue_destroy(queue_t** queue){
  while(!queue_isempty(*queue)){
    dequeue(*queue);  
  }
  queue_free(queue);  
}

/**
 * @brief delete a int stack.
 * 
 * @param stack 
 */
void stack_destroy(stack_t** stack){
  while(!stack_isempty(*stack)){
    pop(*stack);  
  } 
  stack_free(stack); 
}

/**
 * @brief create a int list of the specified size.
 * 
 * @param maxsize 
 * @return list_t* 
 */
list_t* list_int(int maxsize){
  list_t* new = list_new(maxsize);
  srand(time(NULL));
  while(!list_isfull(new)){
    list_insert(new,0,rand()%30);   
  }
  return new;    
}

/**
 * @brief auxilar function for list_traverse.
 * 
 * @param value 
 * @param index 
 * @param ctx 
 * @return true 
 * @return false 
 */
bool look_andPrintf(t_elem value,int index,void* ctx){
  printf("%i ",value);
  return true;    
}

/**
 * @brief auxiliar function for queue_traverse and stack_traverse.
 * 
 * @param value 
 * @param context 
 * @return true 
 * @return false 
 */
bool look_andPrintfElement(t_elem value,void* context){
  printf("%d ",value);
  return true;
}


/**
 * @brief auxiliar function to compare int values.
 * 
 * @param value1 
 * @param value2 
 * @return int 
 */
int compare_int(t_elem value1,t_elem value2){
  return value1-value2;  
}

/**
 * @brief auxiliar procedure to print int values.
 * 
 * @param value 
 */
void printf_int(t_elem value){
  printf("%i ",value);  
}
