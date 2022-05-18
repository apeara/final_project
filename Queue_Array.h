#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Element;

typedef struct {
  Element *queue; // array to store elements
  int size; // maximum size
  int front, rear; // front and rear
} Queue;

Element null = 0;

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

  return pQueue;
}

void EnQueue(Queue *pQueue,Element data){
  if((pQueue->rear+1)%pQueue->size == pQueue->front) {
    printf("공간이 없습니다.");
    return;
  }
  
  pQueue->rear = (pQueue->rear + 1) % (pQueue->size);
  pQueue->queue[pQueue->rear] = data;
}

Element DeQueue(Queue *pQueue){
  Element temp;

  if(pQueue->front == pQueue->rear){
    printf("data가 없음.");
     return null;
  }
  pQueue->front = (pQueue->front + 1) % pQueue->size;
  temp = pQueue->queue[pQueue->front];
  

  return temp;
}


bool FullQueue(Queue *pQueue){
  return ((pQueue->rear+1) % pQueue->size == pQueue->front);
  //return (pQueue.front == pQueue.rear);
}

bool EmptyQueue(Queue *pQueue){
  return (pQueue->front == pQueue->rear);
}

int CountQueue(Queue *pQueue){
  int count=0;
  
  //(pQueue->rear + 1) % (pQueue->size)
  //printf("check");
  for(int i=(pQueue->rear) % (pQueue->size) ;i != pQueue->front;i = (i+1) % (pQueue->size)){
    count++;
  }

  return (pQueue->size - count);
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