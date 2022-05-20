#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Element;

typedef struct tQueueNode {
  Element data;
  struct tQueueNode *next;
} QueueNode;

typedef struct {
  int count; // # of element
  QueueNode *front, *rear; // front and rear
} Queue;

Element null = 0;

Queue* CreateQueue(){
  Queue *pNewQueue = (Queue*)malloc(sizeof(Queue));
  if(pNewQueue == NULL) return NULL;
  pNewQueue->count = 0;
  pNewQueue->front = pNewQueue->rear = NULL;
  return pNewQueue;
}

void EnQueue(Queue *pQueue, Element item){
  QueueNode *pNewNode = (QueueNode*) malloc(sizeof(QueueNode));
  if(pNewNode == NULL) return;
  pNewNode->data = item;
  pNewNode->next = NULL;

  if(pQueue->count <= 0){
    pQueue->front = pNewNode;
    pQueue->rear = pNewNode;
  }  

  else {
    pQueue->rear->next = pNewNode;
    pQueue->rear = pNewNode;
  }

  pQueue->count++;
}

Element DeQueue(Queue *pQueue){
  QueueNode *pFront = NULL;
  Element item = 0;

  if(pQueue->count <= 0) return 0; 

  pFront = pQueue->front;
  item = pFront->data;

  if(pQueue->count == 1){
    pQueue->front = pQueue->rear = NULL;
  } 

  else {
    pQueue->front = pFront->next;
  }

  free(pFront);
  pQueue->count--;
  return item;
}

Element QueueFront(Queue *pQueue){
  if(pQueue->count <= 0) return null;

  else{
    return pQueue->front->data;
  }
}

Element QueueRear(Queue *pQueue){
  if(pQueue->count <= 0) return null;

  else{
    return pQueue->rear->data;
  }
}

bool EmptyQueue(Queue *pQueue){
  return (pQueue->count == 0);
}

bool FullQueue(Queue *pQueue){
  QueueNode *temp;

  temp = (QueueNode*) malloc(sizeof(*(pQueue->rear)));

  if(temp){
    free(temp);
    return true;
  }

  return false;
}

int CountQueue(Queue *pQueue){
  return (pQueue->count);
}

void DestroyQueue(Queue *pQueue){
  QueueNode *pCur = NULL, *pNext = NULL;
  for(pCur = pQueue->front; pCur != NULL; pCur = pNext){
    pNext = pCur->next;
    free(pCur);
  }
  
  pQueue->count = 0;
  pQueue->front = pQueue->rear = NULL;
  free(pQueue);
}
