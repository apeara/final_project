#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
  char name[50];
} Element;

typedef struct {
  Element *queue; // array to store elements
  int size; // maximum size
  int front, rear; // front and rear
  int count;
} Queue;

Element null = {""};

Queue *CreateQueue(int size){
  Queue *pQueue = (Queue *)malloc(sizeof(Queue));
  if(pQueue == NULL) return NULL;

  pQueue->queue = (Element *)malloc(sizeof(Element) * size);

  if(!pQueue->queue){
    free(pQueue);
    return NULL;
  }

  pQueue->size = size;
  pQueue->front = 0;
  pQueue->rear = 0;
  pQueue->count = 0;
  return pQueue;
}

void EnQueue(Queue *pQueue,Element data){
  if((pQueue->rear+1)%pQueue->size == pQueue->front) {
    printf("공간이 없습니다.");
    return;
  }
  
  pQueue->rear = (pQueue->rear + 1) % (pQueue->size);
  pQueue->queue[pQueue->rear] = data;
  pQueue->count++;
}

Element DeQueue(Queue *pQueue){
  Element temp;

  if(pQueue->front == pQueue->rear){
     return null;
  }
  pQueue->front = (pQueue->front + 1) % pQueue->size;
  temp = pQueue->queue[pQueue->front];
  pQueue->count--;
  

  return temp;
}


bool FullQueue(Queue *pQueue){
  return ((pQueue->rear+1) % pQueue->size == pQueue->front);
  //return (pQueue.front == pQueue.rear);
}

bool EmptyQueue(Queue *pQueue){
  return (pQueue->count == 0);
}

int CountQueue(Queue *pQueue){

  return pQueue->count;
}

Element QueueFront(Queue *pQueue){
  return pQueue->queue[pQueue->front];
}

Element QueueRear(Queue *pQueue){
  return pQueue->queue[pQueue->rear];
}


void DestroyQueue(Queue *pQueue){
  Element temp;

  for(int i = pQueue->front ; i != pQueue->rear; i = pQueue->front){
    temp = DeQueue(pQueue);
  }

  free(pQueue->queue);
  free(pQueue);
}
