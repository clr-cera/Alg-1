#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue_* queue;

queue createQueue();
void insertQueue(queue Queue, int value);
int removeQueue(queue Queue);


#endif
