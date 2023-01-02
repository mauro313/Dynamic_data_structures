#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

//Funcion para crear una nueva queue
queue_t* queue_new (int maxsize){
  queue_t* new_queue = (queue_t*)malloc(sizeof(queue_t));
  if(new_queue==NULL){
    printf("memeory cannot be reserved for a new queue");
    exit(-1);  
  } 
  new_queue->head = NULL;
  new_queue->tail = NULL;
  new_queue->maxsize = maxsize;
  new_queue->count = 0;
  return new_queue;   
}

//Procedimiento para liberar la memoria de una queue
void queue_free(queue_t** queue){
  if(queue!=NULL &&  *queue!=NULL){
    (*queue)->head = NULL;
    (*queue)->tail = NULL;
    free(*queue);
    *queue = NULL;  
  }      
}

//funcion para obtener el tamaño de la queue
int queue_getsize(queue_t* queue){
  if(queue == NULL){
    printf("queue pointer is NULL");
    exit(-2);  
  }
  return queue->count;    
} 

//Funcion que devuelve 1 si la queue esta llena y 0 si no lo esta
bool queue_isfull(queue_t* queue){
  if(queue == NULL){
    printf("queue pointer is NULL");
    exit(-3);  
  }
  bool returned = false;
  if(queue->count == queue->maxsize){
    returned = true;  
  }
  return returned;    
} 

//Funcion que devuelve 1 si la queue esta vacia y 0 si no lo esta
bool queue_isempty(queue_t* queue){
  if(queue == NULL){
    printf("queue pointer is NULL");
    exit(-4);  
  }
  bool retuned = false;
  if(queue->count == 0){
    retuned = true;  
  } 
  return retuned;   
} 

// Procedimiento para añadir elemento a la queue.Retorna 1 si se pudo añadir y 0 en caso contrario(queue llena)
int enqueue(queue_t* queue, t_elem elem){
  if(queue == NULL){
    printf("queue pointer is NULL");
    exit(-5);  
  }
  int returned = 0;
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
    returned = 1;      
  }  
  return returned;
} 

// Procedimiento para imprimir el contenido de una queue
void queue_printf(queue_t* queue,void (*printf_elem)(t_elem)){
  if(queue == NULL){
    printf("queue pointer is NULL");
    exit(-6);  
  } 
  for(int i=0;i<queue->count;i++){
    t_elem auxiliar = dequeue(queue);
    printf_elem(auxiliar);
    enqueue(queue,auxiliar);
  }
}

//Funcion para quitar un elemento de la queue
t_elem dequeue(queue_t* queue){ 
  if(queue == NULL){
    printf("queue pointer is NULL");
    exit(-7);  
  } 
  if(queue_isempty(queue)){
    printf("queue is empty");
    exit(-8);  
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

//Funcion que permite conocer el valor inicial de la queue
t_elem peek(queue_t* queue){
  if(queue == NULL){
    printf("queue pointer is NULL");
    exit(-9);  
  } 
  if(queue_isempty(queue)){
    printf("queue is empty");
    exit(-10);  
  }
  return sll_node_get_value(queue->head);
} 

//Procedimiento para recorrer la queue usando una variable de contexto. 
void queue_traverse(queue_t* queue,bool queue_do(t_elem,void*),void* context){
  if(queue == NULL){
    printf("queue pointer is NULL");
    exit(-11);  
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