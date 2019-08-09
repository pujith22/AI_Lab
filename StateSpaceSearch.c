#include<stdio.h>
#include<stdlib.h>

int size = 4;

typedef struct State{
    struct State* parent;
	int arr[4][4];
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
	printf("row: %d\tcolumn: %d",s.posX,s.posY);
    printf("\n");
}

void inputState(state *s)
{
	int i,j;
	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
			scanf("%d",&s->arr[i][j]);
}
void intialize(state *s)
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

state* operation(state* s,int operation )

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
void *data;
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
        printf("%d -> ",temp->data);
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

int isInQueue(queue *q,void* data)
{
    queue_node* temp = q->head;
    while(temp!=NULL)
    {
        if(compareStates((state*)temp->data,(state*)data)==1)
            return 1;
        temp=temp->next;
    }
    return 0;
}


void main()
{
	state initialState,finalState;
	state* newState;
	printf("\nEnter the Initial state configuration: \n");
	inputState(&initialState);
	printf("\nEnter the Final State Configuration: \n");
	inputState(&finalState);
	intialize(&finalState);
	queue q1,q2;
	enqueue(&q1,&initialState);
	/*printState(s);
	state *p = moveUp(s);
	state *q = moveLeft(*p);
	state *r = moveRight(*q);
	state *z = moveDown(*r);
	printState(*p);
	printState(*q);
	printState(*r);
	printState(*z);*/


}

