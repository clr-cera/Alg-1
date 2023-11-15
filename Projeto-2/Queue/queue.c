#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct cell_{
  int value;
  struct cell_* next;
}cellObj;

typedef cellObj* cell; 

typedef struct queue_{
  int length;
  cell begin;
  cell end;
}queueObj;

typedef queueObj* queue;


queue createQueue(){
  queue result = (queue) malloc(sizeof(queueObj));
  
  result->length = 0;
  result->end = NULL;
  result->begin = NULL;

  return result;
}

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

int removeQueue(queue Queue){
  int output = Queue->begin->value;
  cell lastBegin = Queue->begin;

  Queue->begin = Queue->begin->next;
  free(lastBegin);

  return output;
}
