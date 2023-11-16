#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
// Essa é a struct célula que comporá a fila, a qual armazena um valor e aponta para outra célula
typedef struct cell_{
  int value;
  struct cell_* next;
}cellObj;

typedef cellObj* cell; 

// Essa é a struct fila, ela armazena seu tamanho, a célula no início e a no fim
typedef struct queue_{
  int length;
  cell begin;
  cell end;
}queueObj;

typedef queueObj* queue;

// Essa função cria uma fila
queue createQueue(){
  queue result = (queue) malloc(sizeof(queueObj));
  
  result->length = 0;
  result->end = NULL;
  result->begin = NULL;

  return result;
}

// Essa função insere um valor inteiro na ultima posição de uma fila
void insertQueue(queue Queue, int value){
  if(Queue->length == 0){ 
    Queue->end = (cell) malloc(sizeof(cellObj));
    Queue->begin = Queue->end;
  }
  
  else{
    Queue->end->next = (cell) malloc(sizeof(cellObj));
    Queue->end = Queue->end->next;
  }

  Queue->end->value = value;
  Queue->end->next = NULL;

  Queue->length += 1;
}

// Essa função retorna true se a fila estiver vazia e false caso contrário
bool queue_empty(queue Queue){
  if (Queue->length == 0)
  return true;
  else return false;
}

// Essa função remove e retorna o primeiro valor de uma fila
int removeQueue(queue Queue){
  if(queue_empty(Queue))
    return -1;
  int output = Queue->begin->value;
  cell lastBegin = Queue->begin;

  Queue->begin = Queue->begin->next;
  free(lastBegin);
  
  Queue->length -= 1;
  return output;
}

// Essa função apaga uma fila da memória
void eraseQueue(queue Queue) {
  cell current = Queue->begin;

  while (current != NULL){
    cell next = current->next;
    free(current);
    current = next;
  }

  free(Queue);
}

