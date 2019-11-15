#ifndef QUEUE_H
#define QUEUE_H


#include <stdlib.h>
#include "../Boundary/boundary.h"


typedef struct Queue {
  int index;
  Boundary boundary;

  struct Queue *next;
} Queue;

void push(Boundary boundary);

void pop();

#endif
