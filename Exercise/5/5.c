#include <stdio.h>
#include <stdlib.h>
 
struct node
{
    int pid,bt,at,b;
    struct node *ptr;
}*front,*rear,*temp,*front1;

struct process
{
    int pid,bt,at,b;
};
 

void enq(int pd, int at, int bt, int b);
struct node *deq();
int empty();
void display();
void rrs(int qt );
void sort(int m, struct process x[]);


void main()
{  
    int n;
    struct process x[10];
    printf("Enter no. of processes: ");
    scanf("%d",&n);
    for (int i=0; i<n; i++){
        printf("\nEnter arrival and burst time: ");
        scanf("%d %d",&x[i].at,&x[i].bt);
        x[i].b=x[i].bt;
        x[i].pid=i+1;
    }
    sort(n,x);
    for (int i=0; i<n; i++){
        enq(x[i].pid,x[i].bt,x[i].at,x[i].b);
    }
    rrs(3);    
}
 
 
/* Enqueing the queue */
void enq(int pd, int bt, int at, int b)
{
    if (rear == NULL)
    {
        rear = (struct node *)malloc(1*sizeof(struct node));
        rear->ptr = NULL;
        rear->pid = pd;
        rear->bt = bt;
        rear->b = b;
        rear->at = at;
        front = rear;
    }
    else
    {
        temp=(struct node *)malloc(1*sizeof(struct node));
        rear->ptr = temp;
        temp->pid = pd;
        temp->bt = bt;
        temp->b = b;
        temp->at = at;
        temp->ptr = NULL;
        rear = temp;
    }
}
 
/* Displaying the queue elements */
void display()
{
    front1 = front;
 
    if ((front1 == NULL) && (rear == NULL))
    {
        printf("Queue is empty");
        return;
    }
    while (front1 != rear)
    {
        printf("P[%d]\t%d\t%d\n", front1->pid,front1->at,front1->bt);
        front1 = front1->ptr;
    }
    if (front1 == rear)
        printf("P[%d]\t%d\t%d\n", front1->pid,front1->at,front1->bt);
    printf(
}
 
/* Dequeing the queue */
struct node *deq()
{
    struct node *tem;
    front1 = front;
    tem=(struct node *)malloc(1*sizeof(struct node));
    tem->pid=front->pid;
    tem->at=front->at;
    tem->bt=front->bt;
    tem->b=front->b;
    if (front1 == NULL)
    {
        printf("\n Error: Trying to display elements from empty queue");
        return tem;
    }
    else
        if (front1->ptr != NULL)
        {
            front1 = front1->ptr;
            free(front);
            front = front1;
        }
        else
        {
            free(front);
            front = NULL;
            rear = NULL;
        }
    return tem;
}
 

/* Display if queue is empty or not */
int empty()
{
    if ((front == NULL) && (rear == NULL))
        return 0;
    else
        return 1;
}


void rrs(int qt )
{
    int t=1,w;
    struct node *tem;
    tem=(struct node *)malloc(1*sizeof(struct node));
    printf("\nProcess\tArrival\tBurst\tWait\tTurnAround\tComplete\n");
    while(empty()){
        tem=deq();
        if ((tem->bt)<=qt){
            t+=tem->bt;
            w=t-tem->b-tem->at;
            printf("p[%d]\t%d\t%d\t%d\t%d\t\t%d\n",tem->pid,tem->at,tem->b,w,w+tem->b,t);
        }else{
            tem->bt-=qt;
            t+=qt;
            enq(tem->pid,tem->bt,tem->at,tem->b);
        }
    }
}

void sort(int m, struct process x[])
{                                                          
    int i, j;
    struct process t;
                                                               
    for(i = 1; i <= m-1; i++){                              
        for(j = 1; j <= m-i; j++){                            
            if(x[j-1].at >= x[j].at)                                
            {
                t = x[j-1];                                    
                x[j-1] = x[j];                                
                x[j] = t;                                      
            }
           
        }  
       
    }
}



