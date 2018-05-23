// ... ο κώδικάς σας για την υλοποίηση του quicksort
// με pthreads και thread pool...
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <string.h>
#define Maxsize 1000


void welocmeMessage(int *nPtr);
int fillitem();
int n;                                 //Áñéèìüò ìÞêïõò ôçò ïõñÜò.Global variable.
int maxrand;
int message;
//=====================================================================================(struct)
struct cell{          //ÄÞëùóç äïìÞò.
	int data;          //Èá ëáìâÜíåé ìåôáâëçôÝò integer ùò äåäïìÝíá.(Ìçíýìáôá)          
	struct cell *nextcellptr;  //ÄÝéêôçò ãéá ôïí åðüìåíï êüìâï.
	};
typedef struct cell queue;//Óõíþíõìï ôçò äïìÞò Queue
typedef queue *queueptr;//Pointer ðïõ äåß÷íåé ôï Queue
void enqueue(queueptr *headerptr,queueptr *tailptr,int value);
int isEmpty(queueptr headerptr);
void printQueue(queueptr currentptr);
int arr[Maxsize];
void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
int quick_sort(int left, int right);




//=============================================================================================
typedef struct task_data {
	int id;
	int left;
	int right;
	int lchild_id;
	int rchild_id;
}task_data;

typedef struct thread_data {
	pthread_t thread;
	sem_t start;
	task_data* task_range;
}thread_data;

sem_t finish;

//Thread Queue declare
thread_data* thread_pool[4];
int thread_queue_rear, thread_queue_front;
void thread_pool_init();
void puch_thread_queue(thread_data* pthdata);
thread_data* pop_thread_queue();
sem_t thread_mutex;
sem_t thread_flag;
//JOB Queue declare
task_data* job_pool[4];
int jobrear, jobfront;
void task_pool_init();
void push_job_queue(task_data* pjob_data);
task_data* pop_job_queue();
sem_t job_mutex;
sem_t job_flag;

//ÓõíÜñôçóç ðïõ åëÝã÷åé áí ç n&maxrand(global variables) åßíáé ìéêñüôåñç Þ ßóç ôïõ 0.
void welcomeMessage(int *nPtr)
{
	printf("Parralel programming.Assignment number 2 2017-2018!!! \n");
	printf("Give me the lenght of queue(N variable):");
	scanf("%d",&(*nPtr));
	printf("Give maxrand border maxrand:");
	scanf("%d",&maxrand);
	if(*nPtr<=0 ||maxrand<=0)                                             
	{
     while(*nPtr<=0 || maxrand<=0)
	 {
	 	if(*nPtr<=0)
		 {
		 printf("Failed N number.N<=0\nPlease try againN:");
	     scanf("%d",&(*nPtr));
          }
		 if(maxrand<=0)
		 {
		  printf("Failed maxrand<=0\nPlease try againN:");
	      scanf("%d",&maxrand);
	      }
	}
}
	printf("N=%ld\nMaxrand=%ld\n",*nPtr,maxrand);

}//ÔÝëïò óõíÜñôçóçò WeclomeMessage


//Äçìéïõñßá óõíÜñôçóçò ðïõ äçìéïõñãåß ôõ÷ßá  messsage ìå üñéï ôßìçò ôï maxrand ðïõ Ýäùóå ï ÷ñÞóôçò
int fillitem(){
	message=rand()%maxrand;
	return message;
}
 main(void)
{
int item;
int counter;
queueptr headerptr=NULL;
queueptr tailptr=NULL;
srand(time(NULL)); 
welcomeMessage(&n);
int z;
	while(counter<n)
	{
	
		item=fillitem();
		enqueue(&headerptr,&tailptr,item);
	   
	
		++counter;
		}	
	printQueue(headerptr);

	printf("Length=%d\n",counter);
	 
	
}
//Äçìéïõñãßá ïõñÜò
void enqueue(queueptr *headerptr,queueptr *tailptr,int value){
	queueptr newptr;
    newptr = (queue*)malloc(sizeof(queue));
	if(newptr!=NULL)
	{
		newptr->data=value;
		newptr->nextcellptr=NULL;
		
		if(isEmpty(*headerptr))
		{
			*headerptr=newptr;
		}
		else
		{
			(*tailptr)->nextcellptr=newptr;
		}
		*tailptr=newptr;
	}
	else{
		printf("%d not inserted.No memory available.\n",value);
	}
}
//¸ëåã÷ïò Üí o äåßêôçò ôçò ïõñÜò åßíáé 0.
int isEmpty(queueptr headerptr)
{
	return headerptr==NULL;
}
//Åêôýðùóç ïõñÜò
void printQueue(queueptr currentptr)
{
	if(currentptr==NULL)
	{
		printf("Queue is empty.\n\n");
		}
		else{
			printf("The queue is:\n");
			while(currentptr!=NULL)
			{
				printf("%2d-->",currentptr->data);
				currentptr=currentptr->nextcellptr;
				printf("");
			}
		}
		printf("NULL\n");
}

int quick_sort(int left, int right){

    int pivot, i, j, t;
    pivot = arr[left];
    i = left; j = right;

    while(1)
    {
        while( arr[i] < pivot ) i++;
        while( arr[j] > pivot ) j--;    
	   if( i >= j ) break;
        swap(arr+i, arr+j);
	i++;
	j--;
    }
    return j;

}
	







