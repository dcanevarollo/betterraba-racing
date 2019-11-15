#include "queue.h"

int indexCounter = 0;

Queue *init = NULL;
Queue *end = NULL;
Queue *temp = NULL;

void push(Boundary boundary) {
  Queue *newNode = (Queue *) malloc(sizeof(Queue));

  newNode->index = indexCounter++;
  newNode->boundary = boundary;
  newNode->next = NULL;

  if (init == NULL)
    init = newNode;
  else
    end->next = newNode;

  end = newNode;
}

void pop() {
  temp = init;
  init = init->next;
  free(temp);
}
