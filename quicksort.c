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
int n;                                 //Μεταβλητή για το μήκος της ουρά;.Global variable.
int maxrand;
int message;
//=====================================================================================(struct)
struct cell{          //Όρισμα δομής cell.
	int data;          //Περιεχόμενο που περιέχει η δομή cell.          
	struct cell *nextcellptr;  //Δείκτης προς την επόμενη δομή.
	};
typedef struct cell queue;//Δημιουργία μεταβλητής queue που περιέχει struct cell
typedef queue *queueptr;//Δείκτης Queeu
void enqueue(queueptr *headerptr,queueptr *tailptr,int value);//Δήλωση εισάγωγης σε queue
int isEmpty(queueptr headerptr);//Συνάρτηση αν το header της qeueue ειναι ΝULL δλδ δεν δέιχνει πουθένα σε νέο cell
void printQueue(queueptr currentptr);//Εκτύπωση της ουράς
int arr[Maxsize];
void swap(int* a, int* b){
	int temp = *a;             //Αλλαγή των θέσεων μέσα στον πίνακα όταν πραγματοποιείται η qucikshort
	*a = *b;
	*b = temp;
}
int quick_sort(int left, int right);//Όρισμα quickshprt




//=============================================================================================
typedef struct task_data {
	int id;
	int left;                 //όρισμα του δεδομένου μεταξύ threads
	int right;
	int lchild_id;
	int rchild_id;
}task_data;

typedef struct thread_data {
	pthread_t thread;           //Αλλαγή δεδομένων μέσω threads
	sem_t start;
	task_data* task_range;
}thread_data;

sem_t finish;

//Thread Queue δήλωση
thread_data* thread_pool[4];

sem_t thread_mutex;
sem_t thread_flag;
//JOB Queue δήλωση
task_data* job_pool[4];
int jobrear, jobfront;

sem_t job_mutex;
sem_t job_flag;

//Συνάρτηση αρχικό μήνυματος.Ζητάει το μήκος της ουράς εργασιών και το ορίο της maxrand που θα γεμίσει την ουρά με τυχαία δεδομένα
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

}//Τέλος δήλωσης welcomeMessage


//Δήλωση συνάρτησης fillitem 
int fillitem(){
	message=rand()%maxrand;
	return message;
}

//Ξεκινάει η main
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
//Συνάρτιζει που "χτίζει την ουρά"
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
//Επιστρέφει αν ειναι 0.
int isEmpty(queueptr headerptr)
{
	return headerptr==NULL;
}
//Συνάρρτηση που εκτυπώνει την ουρά
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

//Δήλωση quickshort

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
	







