#include <stdlib.h>
#include <stdlib.h>
#include "list.h"

//Funcion para crear una lista nueva
list_t* list_new(int maxsize){ 
  list_t* list = (list_t*) malloc(sizeof(list_t));
  if(list==NULL){
    printf("mamory cannot be reserved for a list pointer");
    exit(-1);  
  }  
  list->head = NULL;
  list->maxsize = maxsize;
  list->count = 0;
  return list;
}

//Procedimiento para liberar la memoria de una lista
void list_free(list_t** list){
  if(list != NULL && *list != NULL){
    (*list)->head = NULL;
    free(*list);
    *list = NULL;  
  }  
}

//Funcion que retorna 1 si la lista esta vacia y 0 si no lo esta
bool list_isempty(list_t* list){
  if(list == NULL){
    printf("list pointer is NULL");
    exit(-2);  
  }
  bool returned = false;
  if(list->count == 0){
    returned = true;  
  }
  return returned;    
}

//Funcion que retorna 1 si la lista esta llena y 0 si no lo esta
bool list_isfull(list_t* list){
  if(list == NULL){
    printf("list pointer is NULL");
    exit(-3);  
  }
  bool returned = false;
  if(list->count == list->maxsize){
    returned = true;  
  }
  return returned; 
}

//Funcion que retorna el tamaño de la lista
int list_length(list_t* list){
  if(list == NULL){
    printf("list pointer is NULL");
    exit(-4);  
  }
  return list->count;   
}

//Procedimiento que permite insertar un elemento en la lista.Retorna 1 si pudo insertarse y 0 en caso contrario(lista llena).
int list_insert(list_t* list, int index, t_elem elem){
  if(list == NULL){
    printf("list pointer is NULL");
    exit(-5);  
  }
  if(index<0 || index>list->count){
    printf("invalid index");
    exit(-6);  
  }
  int returned = 0;
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
    returned = 1;
  } 
  return returned;
}

//Funcion que permite obtener un elemento de la lista
t_elem list_get(list_t* list, int index){
  if(list == NULL){
    printf("list pointer is NULL");
    exit(-7);  
  }
  if(index<0 || index>=list->count){
    printf("invalid index");
    exit(-8);    
  }
  sll_node_t* auxiliar = list->head;
  int count = 0;
  while(count < index){
    auxiliar = sll_node_get_next(auxiliar);
    count++;  
  } 
  return  sll_node_get_value(auxiliar);
}

//Funcion que retorna el indice de la lista del elemento si este se encuentra, y retorna
//el tamaño de la lista si no.
int list_search(list_t* list, t_elem elem, int (*compare)(t_elem,t_elem)){
  if(list == NULL){
    printf("list pointer is NULL");
    exit(-9);  
  }  
  int returned = 0;
  sll_node_t* auxiliar = list->head;
  while(auxiliar!=NULL && compare(sll_node_get_value(auxiliar),elem)!=0){
    auxiliar = sll_node_get_next(auxiliar);
    returned++;  
  }
  return returned;
}

//Procedimiento para remover un elemento de la lista
void list_delete(list_t* list, int index){
  if(list == NULL){
    printf("list pointer is NULL");
    exit(-10);
  } 
  if(index<0 || index>=list->count){
    printf("invalid index");
    exit(-11);  
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

//Procedimeinto para recorrer la lista bajo una condicion y un contexto determinado
void list_traverse(list_t *L, bool look(t_elem elem, int index, void *ctx), void *ctx){
  if(L == NULL){
    printf("list pointer is NULL");
    exit(-12);  
  }
  sll_node_t* node = L->head;
  int index = 0;
  while (sll_node_get_next(node)!=NULL && look(sll_node_get_value(node), index, ctx)) {
    node = sll_node_get_next(node);
    index++;
  }
}