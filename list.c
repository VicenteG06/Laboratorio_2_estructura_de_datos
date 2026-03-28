#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

// 1. Programe la función List* createList(), la cual retorna el puntero del tipo de dato List con sus valores inicializados en NULL.
// Recuerda reservar memoria al puntero usando malloc o calloc.

List * createList() {
    List * list = malloc(sizeof(List));
    list -> head = NULL;
    list -> tail = NULL;
    list -> current = NULL;
    return list;
}

// 2. Programe las funciones void * firstList(List * list) y void * nextList(List * list).
//   - La primera retorna el dato del primer nodo de la lista (head) y actualiza el current para que apunte a ese nodo.
//   - La segunda función retorna el dato del nodo a continuación del current y actualiza el current para que

void * firstList(List * list) {
    if(list -> head == NULL) return NULL;
    list -> current = list -> head;
    void* dato = list -> current -> data;
    return dato;
}

void * nextList(List * list) {
    if(list -> current == NULL) return NULL;
    if(list -> current -> next == NULL) return NULL;
    void *dato = list -> current -> next -> data;
    list -> current = list -> current -> next;
    return dato;
}

// 3. Programe las funciones void * lastList(List * list) y void * prevList(List * list).
//   - La primera retorna el dato del último elemento en la lista y actualiza el current al nodo correspondiente.
//   - La segunda función retorna el dato del nodo anterior a current y actualiza el current para que apunte a ese nodo.

void * lastList(List * list) {
    if(list -> tail == NULL) return NULL;
    void *dato = list -> tail -> data;
    list -> current = list -> tail;
    return dato;
}

void * prevList(List * list) {
    if(list -> current == NULL) return NULL;
    if(list -> current -> prev == NULL) return NULL;
    void *dato = list -> current -> prev -> data;
    list -> current = list -> current -> prev;
    return dato;
}

// 4. Programe la función void pushFront(List * list, void * data), la cual agrega un dato al comienzo de la lista.
// Puede utilizar la función Node* createNode(void * data) la cual crea, incializa y retorna un nodo con el dato correspondiente.

void pushFront(List * list, void * data) {
    Node* nuevo_nodo = createNode(data);
    if(list -> head == NULL){
        list -> head = nuevo_nodo;
        list -> tail = nuevo_nodo;
    } 
    else{
        nuevo_nodo -> next = list -> head;
        list -> head = nuevo_nodo;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list, data);
}

// 5. Programe la función void pushCurrent(List * list, void* data), la cual agrega un dato a continuación del nodo apuntado por list->current.

void pushCurrent(List * list, void * data) {
    Node* nuevo_nodo = createNode(data);
    if(list -> current == list -> head){
        nuevo_nodo -> next = list -> head -> next;
        nuevo_nodo -> prev = list -> head;
        list -> head -> next = nuevo_nodo;
    }
    else if(list -> current -> next == NULL){
        nuevo_nodo -> prev = list -> current;
        list -> current -> next = nuevo_nodo;
        list -> tail = nuevo_nodo;
    }
    else{
        nuevo_nodo -> prev = list -> current;
        nuevo_nodo -> next = list -> current -> next;
        list -> current = nuevo_nodo;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

// 6. Programe la función void* popCurrent(List * list), la cual elimina el nodo que está en la posición del current de la lista enlazada, y además retorna el dato del nodo eliminado.
// Nota: El current debe quedar apuntando al nodo siguiente del eliminado.

void * popCurrent(List * list) {
    void* dato = list -> current -> data;
    if(list -> current == list -> head){
        list -> head = list -> current -> next;
        list -> head -> prev = NULL;
        list -> current = list -> current -> next;
    }
    else if(list -> current == list -> tail){
        list -> tail = list -> current -> prev;
        list -> tail -> next = NULL;
        list -> current = NULL;
    }
    else{
        Node* izq = list -> current -> prev;
        Node* der = list -> current -> next;
        list -> current = der;
        der -> prev = izq;
        izq -> next = der;
    }
    return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
