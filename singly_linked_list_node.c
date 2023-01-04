#include <stdlib.h>
#include <stdio.h>
#include "singly_linked_list_node.h"
// varias de las funciones pueden realizarse utilizando la recursividad. El problema radica en la
//complejidad espacial

//se crea un nuevo nodo.
sll_node_t* sll_node_new(t_elem value){
  sll_node_t* new_node = (sll_node_t*)malloc(sizeof(sll_node_t));
  if(new_node == NULL){
    printf("memory cannot be reserved for a new sll_node");
    exit(-1);
  }
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

//Procedimiento para liberar la memoria de un nodo
void sll_node_free(sll_node_t** node){
  if(node != NULL && *node!=NULL){
    (*node)->next = NULL;
    free(*node);
    *node = NULL;
  }
}

//funcion que retorna el valor de un nodo
t_elem sll_node_get_value(sll_node_t* node){
  if(node == NULL){
    printf("sll_node pointer is null");
    exit(-2);
  }
  return node->value;
}

// funcion que retorna true en caso de el siguiente sea nulo y false en caso contrario
bool sll_node_nextisnull(sll_node_t* node){
  if(node == NULL){
    printf("sll_node pointer is null");
    exit(-3);
  }
  bool returned = false;
  if(node->next == NULL){
    returned =true;
  }
  return returned;
}

// retorna el nodo siguiente
sll_node_t* sll_node_get_next(sll_node_t* node){
  if(node == NULL){
    printf("sll_node pointer is null");
    exit(-4);
  }
  return node->next;
}

// retorna la referencia del nodo siguiente
sll_node_t** sll_node_get_next_referece(sll_node_t* node){
  if(node == NULL){
    printf("sll_node pointer is null");
    exit(-5);
  }
  return &node->next;
}

// funcion que conecta dos nodos.Devuelve 1 si se conectaron y 0 en caso contrario(*origin = null).
int sll_node_link_node(sll_node_t** origin,sll_node_t* destiny){
  if(origin == NULL){
    printf("sll_node double pointer is NULL");
    exit(-6);
  }
  int returned = 0;
  if(*origin != NULL){
    (*origin)->next = destiny;
    returned = 1;
  }
  return returned;
}

// procedimiento para insertar un nodo al final de una lista de nodos
// version iterativa
void sll_node_add_node_end_iterative(sll_node_t** head,sll_node_t* new_node){
  if(head == NULL){
    printf("sll_node double pointer is NULL");
    exit(-7);
  }
  if(*head == NULL){
    *head = new_node;
  }
  else{
    sll_node_t* aux = *head;
    while(aux->next!=NULL){
      aux = aux->next;
    }
    aux->next = new_node;
  }
}

//version recursiva de la insercion de un nodo al final de la lista
void sll_node_add_node_end_recursive(sll_node_t** head,sll_node_t* new_node){
  if(head == NULL){
    printf("sll_node double pointer is NULL");
    exit(-8);
  }
  if(*head == NULL){
    *head = new_node;
  }
  else{
    sll_node_add_node_end_recursive(&(*head)->next,new_node);
  }
}

// inserta un valor al final de la lista.
void sll_node_add_value_end(sll_node_t** head,t_elem value){
  if(head == NULL){
    printf("sll_node double pointer is NULL");
    exit(-9);
  }
  sll_node_t* new_node = sll_node_new(value);
  sll_node_add_node_end_iterative(head,new_node);
}

// inserta un valor al inicio de la lista
void sll_node_add_value_first(sll_node_t** head,t_elem value){
  if(head == NULL){
    printf("sll_node double pointer is NULL");
    exit(-10);
  }
  sll_node_t* new_node = sll_node_new(value);
  new_node->next = *head;
  *head = new_node;
}

//imprime un nodo
void sll_node_printf(sll_node_t* node,void (*print)(t_elem)){
  if(node == NULL){
    printf("sll_node pointer is NULL");
    exit(-11);
  }
  print(node->value);
}

// imprime todos los nodos de la lista. Version iterativa
void sll_node_all_printf_iterative(sll_node_t* head,void (*print)(t_elem)){
  if(head == NULL){
    printf("sll_node pointer is null\n\n");
    exit(-12);
  }
  sll_node_t* auxiliar = head;
  while(auxiliar!=NULL){
    print(auxiliar->value);
    auxiliar = auxiliar->next;
  }
}

//imprime todos los nodos de la lista.Version recursiva
void sll_node_all_printf_recursive(sll_node_t* head,void (*print)(t_elem)){
  if(head == NULL){
    printf("\n");
  }
  else{
    print(head->value);
    sll_node_all_printf_recursive(head->next,print);
  }
}

// retorna la referencia del nodo buscado si se encuentra, en caso contrario retorna NULL. Uso
// de recursividad
sll_node_t** sll_node_search_recursive(sll_node_t** head,t_elem value,int(*compare)(t_elem,t_elem)){
  if(head == NULL){
    printf("sll_node double pointer is NULL");
    exit(-13);
  }
  sll_node_t** auxiliar = NULL;
  if(*head!=NULL && compare(sll_node_get_value(*head),value)!=0){
    auxiliar = sll_node_search_recursive(&(*head)->next,value,compare);
  }
  else{
    auxiliar = head;
    if(*auxiliar == NULL){
      auxiliar = NULL;
    }
  }
  return auxiliar;
}

// retorna la referencia del nodo buscado si se encuentra, en caso contrario retorna NULL.
//version iterativa.
sll_node_t** sll_node_search_iterative(sll_node_t** head,t_elem value,int (*compare)(t_elem,t_elem)){
  if(head == NULL){
    printf("sll_node double pointer is NULL");
    exit(-14);
  }
  sll_node_t** auxiliar = head;
  while((*auxiliar)!=NULL && compare((*auxiliar)->value,value)!=0){
    auxiliar = &(*auxiliar)->next;
  }
  if(*auxiliar == NULL){
    auxiliar == NULL;
  }
  return auxiliar;
}

// remueve un nodo de la lista que coincida con el valor buscado y lo retorna si se encuentra. Caso contrario
//retorna NULL.
sll_node_t* sll_node_remove(sll_node_t** head,t_elem value,int (*compare)(t_elem,t_elem)){
  if(head == NULL){
    printf("sll_double pointer is NULL");
    exit(-15);
  }
  sll_node_t* node_to_remove =NULL;
  sll_node_t* auxiliar = *head;
  sll_node_t* prev = NULL;
  while((auxiliar!= NULL) && (compare(auxiliar->value,value)==0)){
    prev=auxiliar;
    auxiliar=auxiliar->next;
  }
  if(auxiliar!=NULL){
    node_to_remove = auxiliar;
    if(prev == *head){
      *head = auxiliar->next;
    }
    else{
      prev->next = auxiliar->next;
    }
    node_to_remove->next = NULL;
  }
  return auxiliar;
}



