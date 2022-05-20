
#include <stdio.h>
#include "Queue_Array2.h"

/*
typedef struct {
  int count; // # of element
  QueueNode *front, *rear; // front and rear
} Queue;

typedef struct{
  char name[50];
} Element;
*/

int main(void) {
  //변수
  Queue *queue;
  int check;
  Element custermer;
  Element temp;
  char c;

  queue = CreateQueue(50);

  repeat : 
  printf("In (0), out (1), exit(2) : ");
  scanf("%d",&check);
  scanf("%c",&c);
  
  switch(check){
    case 0:
      printf("Custermer : ");
      scanf("%[^\n]s",custermer.name);

      EnQueue(queue,custermer);
      //printf("%d",CountQueue(queue));
    break;

    case 1:
      if(EmptyQueue(queue)){
        printf("Queue is empty !\n");
        break;
      }

      else printf("Customer dequeued : %s\n",DeQueue(queue).name);
    break;

    case 2:
      printf("exit.");
      exit(0);
    break;

    default:
      printf("0,1,2 중 하나를 입력하세요.");
    break;
  }
  
  printf("The current status of Queue : (");
  
  if(CountQueue(queue)>=2){
    //printf("check1\n");
    for(int i=0;i<CountQueue(queue)-1;i++){
      temp = DeQueue(queue);
      printf("%s%d ,",temp.name,i+1);
      EnQueue(queue,temp);
    }
    temp = DeQueue(queue);
    printf("%s%d",temp.name,CountQueue(queue)+1);
    EnQueue(queue,temp);
  }
  else if(CountQueue(queue)==1){
    //printf("check2\n");
    temp = DeQueue(queue);
    printf("%s1",temp.name);
    EnQueue(queue,temp);
  }
  else if(CountQueue(queue)==0){
    printf(" ");
  }
  
  /*for(int i=0;i<CountQueue(queue);i++){
    temp = DeQueue(queue);
    printf("%s ,",temp.name);
    EnQueue(queue,temp);
  }*/

  printf(")\n\n\n\n");

  goto repeat;
  DestroyQueue(queue);
  return 0;
}
