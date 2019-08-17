#include<stdio.h>
#include<stdlib.h>
#define size 3

typedef struct State{
    struct State* parent;
	int arr[size][size];
	int posX;
	int posY;
	int operation;
}state;

void printState(state s)
{
	int i,j;
	printf("\n");
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
			printf("%d\t",s.arr[i][j]);
		printf("\n");

	}
	printf("\n");
}

void inputState(state *s)
{
	int i,j;
	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
			scanf("%d",&s->arr[i][j]);
}
void initializeState(state *s)
{
	int i,j;
	s->parent = NULL;
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
			if(s->arr[i][j]==-1)
			{
				s->posX = i;
				s->posY = j;
				return;
			}
	}
}

//operation1
state* moveUp(state s)
{

	if(s.posX==0)
		return NULL;

	state* temp = (state*)malloc(sizeof(state));
	int i,j;
	for(i=0;i<size;i++)
	{
		for (j=0;j<size;j++)
			temp->arr[i][j] = s.arr[i][j];
	}

	temp->posX = s.posX;
	temp->posY = s.posY;
	temp->arr[temp->posX][temp->posY] =  temp->arr[temp->posX-1][temp->posY];
	temp->arr[temp->posX-1][temp->posY] = -1;
	temp->posX = temp->posX -1;
	return temp;
}

//operation2
state* moveDown(state s)
{

	if(s.posX==size-1)
		return NULL;

	state* temp = (state*)malloc(sizeof(state));
	int i,j;
	for(i=0;i<size;i++)
	{
		for (j=0;j<size;j++)
			temp->arr[i][j] = s.arr[i][j];
	}

	temp->posX = s.posX;
	temp->posY = s.posY;
	temp->arr[temp->posX][temp->posY] =  temp->arr[temp->posX+1][temp->posY];
	temp->arr[temp->posX+1][temp->posY] = -1;
	(temp->posX)++;
	return temp;
}

//operation3
state* moveLeft(state s)
{

	if(s.posY==0)
		return NULL;

	state* temp = (state*)malloc(sizeof(state));
	int i,j;
	for(i=0;i<size;i++)
	{
		for (j=0;j<size;j++)
			temp->arr[i][j] = s.arr[i][j];
	}

	temp->posX = s.posX;
	temp->posY = s.posY;
	temp->arr[temp->posX][temp->posY] =  temp->arr[temp->posX][temp->posY-1];
	temp->arr[temp->posX][temp->posY-1] = -1;
	temp->posY = temp->posY-1;
	return temp;
}

//operation4
state* moveRight(state s)
{

	if(s.posY==size-1)
		return NULL;

	state* temp = (state*)malloc(sizeof(state));
	int i,j;
	for(i=0;i<size;i++)
	{
		for (j=0;j<size;j++)
			temp->arr[i][j] = s.arr[i][j];
	}

	temp->posX = s.posX;
	temp->posY = s.posY;
	temp->arr[temp->posX][temp->posY] =  temp->arr[temp->posX][temp->posY+1];
	temp->arr[temp->posX][temp->posY+1] = -1;
	temp->posY = temp->posY + 1;
	return temp;
}

state* operation(state* s,int operation)
{
    state* temp;
    switch(operation)
    {
        case 1:
            temp = moveUp(*s);
        break;
        case 2:
            temp = moveDown(*s);
        break;
        case 3:
            temp = moveLeft(*s);
        break;
        case 4:
            temp = moveRight(*s);
        break;
        default:
            temp = NULL;
    }
    return temp;
}

int compareStates(state *a,state *b)
{
	int i,j;
	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
		{
			if(a->arr[i][j]!= b->arr[i][j])
				return 0;
		}
	return 1;
}

typedef struct QueueNode{
void* data;
struct QueueNode* next;
}queue_node;

typedef struct Queue{
struct QueueNode *head;
struct QueueNode *tail;
}queue;

queue_node* createNode(void* data)
{
    queue_node* temp = (queue_node*)malloc(sizeof(queue_node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void initializeQueue(queue* q)
{
    q->head = q->tail =NULL;
}

void enqueue(queue* q,void* data)
{
    if(q->head==NULL)
        q->head = q->tail = createNode(data);
    else{
        q->tail->next = createNode(data);
        q->tail = q->tail->next;
    }

}

queue_node* dequeue(queue *q)
{
    if(q->head==NULL)
        return NULL;
    else{
        queue_node* temp = q->head;
        q->head = q->head->next;
        return temp;
    }
}

void printQueue(queue *q)
{
    printf("\n");
    if(q->head==NULL)
        printf("Nothing to Print Here!\n");
    else
    {
    queue_node* temp = q->head;

    while(temp!=NULL)
    {
        printf("%d -> ",*(int*)temp->data);
        temp = temp->next;
    }
    printf("\n");
    }
}

int isEmpty(queue *q)
{
    if(q->head==NULL)
        return 1;
    else
        return 0;
}

int isInQueue(queue *q,state* data)
{
    queue_node* temp = q->head;
    while(temp!=NULL)
    {
        if(compareStates((state*)temp->data,data)==1)
            return 1;
        temp=temp->next;
    }
    return 0;
}

void backtrack(state* FinalState)
{
    state* temp = FinalState;
   while(temp!=NULL)
   {
       printf("\n--------------------------------------------\n");
       printState(*temp);
       temp = temp->parent;
   }
   printf("\n\n");
}


void main()
{
	state initialState,finalState;
	state* newState;
	state* s;          //For temporary Usage
	queue q1,q2;                // For Fringe and visited states.
	initializeQueue(&q1);
	initializeQueue(&q2);
	int i;
	printf("\nEnter the Initial state configuration (-1 for blank Tile): \n");
	inputState(&initialState);
	initializeState(&initialState);
	printf("\nEnter the Final State Configuration (-1 for blank Tile): \n");
	inputState(&finalState);
	initializeState(&finalState);
	printf("\n\nInitial State: \n\n");
	printState(initialState);
	printf("\n\nFinal State: \n\n");
	printState(finalState);
	printf("\nOPERATIONS: \n");

	enqueue(&q1,&finalState);
	while(isEmpty(&q1)!=1)
    {
       s = (state*)(dequeue(&q1)->data);
       enqueue(&q2,s);
       if(compareStates(s,&initialState)==1)
       {
           backtrack(s);
           break;
       }

       for(i=1;i<5;i++)
       {
           newState = operation(s,i);

            if(newState!=NULL)
            {
                newState->operation = i;
                if(isInQueue(&q2,newState)==0)
                {
                    newState->parent = s;
                    enqueue(&q1,newState);

                }
                else
                	free(newState);
            }


       }
    }

    if(isEmpty(&q1))
		printf("\nFinal State is not possible from the initial configuration provided. Sorry!\n\n ");

}
