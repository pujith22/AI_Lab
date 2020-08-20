#include<stdio.h>   // For standard input/output
#include<stdlib.h>  // for malloc and other function..
#include<time.h> //for calculating time(i.e for clock() function)
#include<windows.h> // for using Sleep(ms) in windows environment.
#define size 3      // size to define size*size state puzzle(can be changed to our requirement)

//Structure definition
typedef struct State {
	struct State* parent;
	int arr[size][size];
	int posX;
	int posY;
	int operation;
	int cost;
	int heuristic;
} state;


//Method for printing the state on the console.
// Currently written for interative printing.
void printState(state s)
{
	system("cls");
	int i, j;
	printf("\n\n\n\n");
	for (i = 0; i < size; i++)
	{
		printf("\t\t\t\t\t");
		for (j = 0; j < size; j++)
		{
			if (s.arr[i][j] != -1)
				printf("%d\t", s.arr[i][j]);
			else
				printf("\t");
		}
		printf("\n\n");

	}

	printf("\n\n");
	Sleep(600);
	switch (s.operation)
	{
	case 1:
		printf("\tUpcoming Step: Slide up");
		break;
	case 2:
		printf("\tUpcoming Step: Slide down");
		break;
	case 3:
		printf("\tUpcoming Step: Slide Left");
		break;
	case 4:
		printf("\tUpcoming Step: Slide Right");
		break;
	default:
		printf("\n");
	}
	Sleep(500);

}

//Module for inputting the state.
void inputState(state *s)
{
	int i, j;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			scanf("%d", &s->arr[i][j]);
}

int mod(int a)
{
	if (a < 0)
		return -a;
	else
		return a;
}

/* Heuristic funcions */

int misplaced_heuristic(state*s1, state*s2)
{
	int count = 0;
	int i, j;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			if (s1->arr[i][j] != s2->arr[i][j])
				count++;
	return count;
}

int manhattan_heuristic(state *s1, state *s2)
{
	int i, j, m, n;
	int manhat = 0;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
		{
			for (m = 0; m < size; m++)
				for (n = 0; n < size; n++)
					if (s1->arr[i][j] == s2->arr[m][n])
						manhat += mod(i - m) + mod(j - n);
		}
	return manhat;

}

/* End of Heuristic Functions */

/* Module for initializing the state */

void initializeState(state *s)
{
	int i, j;
	s->parent = NULL;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
			if (s->arr[i][j] == -1)
			{
				s->posX = i;
				s->posY = j;
				return;
			}
	}
	s->operation = 0;
	s->heuristic = 0;

}
/* Operation definitions */
//operation1
state* moveUp(state s)
{

	if (s.posX == 0)
		return NULL;

	state* temp = (state*)malloc(sizeof(state));
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
			temp->arr[i][j] = s.arr[i][j];
	}

	temp->posX = s.posX;
	temp->posY = s.posY;
	temp->arr[temp->posX][temp->posY] =  temp->arr[temp->posX - 1][temp->posY];
	temp->arr[temp->posX - 1][temp->posY] = -1;
	temp->posX = temp->posX - 1;
	return temp;
}

//operation2
state* moveDown(state s)
{

	if (s.posX == size - 1)
		return NULL;

	state* temp = (state*)malloc(sizeof(state));
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
			temp->arr[i][j] = s.arr[i][j];
	}

	temp->posX = s.posX;
	temp->posY = s.posY;
	temp->arr[temp->posX][temp->posY] =  temp->arr[temp->posX + 1][temp->posY];
	temp->arr[temp->posX + 1][temp->posY] = -1;
	(temp->posX)++;
	return temp;
}

//operation3
state* moveLeft(state s)
{

	if (s.posY == 0)
		return NULL;

	state* temp = (state*)malloc(sizeof(state));
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
			temp->arr[i][j] = s.arr[i][j];
	}

	temp->posX = s.posX;
	temp->posY = s.posY;
	temp->arr[temp->posX][temp->posY] =  temp->arr[temp->posX][temp->posY - 1];
	temp->arr[temp->posX][temp->posY - 1] = -1;
	temp->posY = temp->posY - 1;
	return temp;
}

//operation4
state* moveRight(state s)
{

	if (s.posY == size - 1)
		return NULL;

	state* temp = (state*)malloc(sizeof(state));
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
			temp->arr[i][j] = s.arr[i][j];
	}

	temp->posX = s.posX;
	temp->posY = s.posY;
	temp->arr[temp->posX][temp->posY] =  temp->arr[temp->posX][temp->posY + 1];
	temp->arr[temp->posX][temp->posY + 1] = -1;
	temp->posY = temp->posY + 1;
	return temp;
}

/* End of operation definitions */


// utility method to operate by passing the operation id.
state* operation(state* s, int operation)
{
	state* temp;
	switch (operation)
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
		temp = NULL; // this won't be called anyway.
	}
	return temp;
}

// Utility-Module to compare two states.
int compareStates(state *a, state *b)
{
	int i, j;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
		{
			if (a->arr[i][j] != b->arr[i][j])
				return 0;
		}
	return 1;
}

/* Start of queue definitions (using generic void pointer for the data)
   So that we can point to any type of data, i.e we are storing pointers
   of the data in the queue actually, instead of actual data*/

typedef struct QueueNode {
	void* data;
	struct QueueNode* next;
} queue_node;

typedef struct Queue {
	struct QueueNode *head;
	struct QueueNode *tail;
} queue;

queue_node* createNode(void* data)
{
	queue_node* temp = (queue_node*)malloc(sizeof(queue_node));
	temp->data = data;
	temp->next = NULL;
	return temp;
}

void initializeQueue(queue* q)
{
	q->head = q->tail = NULL;
}
void enqueue(queue* q, void* data)
{
	if (q->head == NULL)
		q->head = q->tail = createNode(data);
	else {
		q->tail->next = createNode(data);
		q->tail = q->tail->next;
	}

}

queue_node* dequeue(queue *q)
{
	if (q->head == NULL)
		return NULL;
	else {
		queue_node* temp = q->head;
		q->head = q->head->next;
		return temp;
	}
}

void printQueue(queue *q)
{
	printf("\n");
	if (q->head == NULL)
		printf("Nothing to Print Here!\n");
	else
	{
		queue_node* temp = q->head;

		while (temp != NULL)
		{
			printf("%d -> ", *(int*)temp->data);
			temp = temp->next;
		}
		printf("\n");
	}
}

int isEmpty(queue *q)
{
	if (q->head == NULL)
		return 1;
	else
		return 0;
}

int isInQueue(queue *q, state* data)
{
	queue_node* temp = q->head;
	while (temp != NULL)
	{
		if (compareStates((state*)temp->data, data) == 1)
			return 1;
		temp = temp->next;
	}
	return 0;
}

/* End of our Abstract-Queue definitions */

/* start of our min_heap requirements and definitions..
   using void pointers so that they can point to any data-type
   here we are using them specifically for our state structure*/

typedef struct Heap_node
{
	void* data;
	int key;
} heap_node;

typedef struct Heap {
	heap_node* arr;
	int n;
} heap;

void initializeMinHeap(heap* h, int size1)
{
	h->arr = (heap_node*) calloc (sizeof(heap_node*), size1);
	h->n = -1;
}

void minHeapifyUp(heap* h, int i)
{
	if (i == 0)
		return;
	else if (h->arr[i].key < h->arr[(i - 1) / 2].key)
	{
		heap_node temp = h->arr[i];
		h->arr[i] = h->arr[(i - 1) / 2];
		h->arr[(i - 1) / 2] = temp;
		minHeapifyUp(h, (i - 1) / 2);
	}
}

void minHeapifyDown(heap* h, int i)
{
	int smallIndex = i;
	if ((2 * i) >= h->n)
		return;
	else
	{

		if (h->arr[2 * i + 1].key < h->arr[smallIndex].key)
			smallIndex = 2 * i + 1;
		if (h->arr[2 * i + 2].key < h->arr[smallIndex].key)
			smallIndex = 2 * i + 2;
		if (smallIndex == i)
			return;
		else {
			heap_node temp = h->arr[i];
			h->arr[i] =  h->arr[smallIndex];
			h->arr[smallIndex] = temp;
			minHeapifyDown(h, smallIndex);
		}

	}
}

void* extractMin(heap *h)
{
	void* temp = h->arr[0].data;
	if (h->n == -1)
		return NULL;
	else {
		h->arr[0] = h->arr[h->n];
		--(h->n);
		minHeapifyDown(h, 0);
	}
	return temp;
}

void minHeapInsert(heap *h, void* data, int key)
{
	++(h->n);
	h->arr[h->n].data = data;
	h->arr[h->n].key = key;
	minHeapifyUp(h, h->n);
}

/* End of min-heap definition and requirements */

/* function to go through the goal state to initial state
    picking up parent of the current node every time
    returns no of steps required as well */
int backtrack(state* FinalState)
{
	state* temp = FinalState;
	//when parent is null, it implies that it is our initial state.
	int steps = 0;
	while (temp->parent != NULL)
	{
		steps += 1;
		printState(*temp);
		temp = temp->parent;
	}
	//printing that to the console.
	printState(*temp);
	return steps;
}


int main()
{
	//pujith22();
	clock_t begin, end;
	state initialState, finalState;     //for capturing initial and final state.
	state* newState;
	state* s;
	heap q1;                    //heap for fringe nodes (yet to be processed according to thier f(n) = c(n)+g(n) values)
	queue q2;                   // For visited states (for handling repeating states).
	initializeMinHeap(&q1, 1000000);    //Heap initialization
	initializeQueue(&q2);               // queue initialization
	int i;

	//inputing states and initializing them

	printf("\nEnter the Initial state configuration (-1 for blank Tile): \n");
	inputState(&initialState);
	printf("\nEnter the Final State Configuration (-1 for blank Tile): \n");
	inputState(&finalState);
	initializeState(&initialState);
	initializeState(&finalState);


	//Priniting initial and final states to the console
	printState(initialState);
	printf("\n\nAbove is our initial state...");
	Sleep(3000);
	printState(finalState);
	printf("\n\nAbove is our goal state...");
	Sleep(3000);

	//printf("\nOPERATIONS: \n");
	finalState.cost = 0;
	finalState.heuristic = misplaced_heuristic(&initialState, &finalState);  //Manhattan_heuristic can also be used, here I am using this.(U can change if you want)
	//initialising the heap with finalstate from which initial state to be found
	minHeapInsert(&q1, &finalState, finalState.heuristic);
	//start clock
	int steps = 0;
	begin = clock();
	while (q1.n != -1)
	{
		//extracting the node with minimum f(n) value from heap.
		s = (state*)(extractMin(&q1));
		// Putting this to the visited queue.
		enqueue(&q2, s);
		// For finding whether we find the goal state or not.
		if (compareStates(s, &initialState) == 1)
		{
			//end timer once we find the goal state.
			end = clock();
			// backtrack to print the path(or set of operations) to the console.
			steps = backtrack(s);
			break;
		}

		//Else calling all 4 possible operations.
		for (i = 1; i < 5; i++)
		{
			//generating the newstate and storing it in this variable.
			newState = operation(s, i);

			// If the state is valied (if it is null invalid operation, hence discard)
			if (newState != NULL)
			{
				// capturing the operation can be used for later purposes(not has any significant use now).
				// can be used to display set of operations to be performed.
				newState->operation = i;
				// checking if new state is in the visited queue,if so, discard.
				if (isInQueue(&q2, newState) == 0)
				{
					// pointing the parent value to the node from which it is generated.
					newState->parent = s;
					// c(n) which is generation cost from the initial state.
					newState->cost = 1 + newState->parent->cost;
					// f(n) = c(n)+h(n) heuristic value (here I am using manhattan_heuristic, misplaced_heuristic can also be used.)
					newState->heuristic = newState->cost + manhattan_heuristic(newState, &initialState);
					// inserting the newstate to our min-heap(our priority-queue) with f(n) as its key..
					minHeapInsert(&q1, newState, newState->heuristic);
				}
				// the state is obsolete, freeing the memory if it is found in the visited queue.
				else
					free(newState);
			}
		}
	}

	if (q1.n == -1)
		printf("\nFinal State is not possible from the initial configuration provided. Sorry!\n\n ");
	//Finally printing the time taken to our console.
	printf("\n\n\tOptimal no of steps needed to reach our goal state is: %d operations", steps);
	printf("\n\n\tTime taken by our A* algorithm to find the optimal solution (i.e with minimum no of operations to reach goal state) is: %.3lf Seconds.\n", ((double)end - begin) / CLOCKS_PER_SEC);
	return 0;
}

/*sample input:
	8 7 6
	5 4 3
	2 1 -1

	1 2 3
	4 5 6
	7 8 -1
*/