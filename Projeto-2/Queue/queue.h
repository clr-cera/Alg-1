#ifndef QUEUE_H
#define QUEUE_H

#include "stdbool.h"

typedef struct queue_* queue;
typedef struct queue_ QUEUE;

queue createQueue();
void eraseQueue(queue Queue);

void insertQueue(queue Queue, int value);
int removeQueue(queue Queue);

bool queue_empty(queue Queue);


#endif
