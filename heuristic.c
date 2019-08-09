#include<stdio.h>
#include<stdlib.h>

#define size 4

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
}

void inputState(state *s)
{
	int i,j;
	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
			scanf("%d",&s->arr[i][j]);
}

int misplaced_heuristic(state*s1,state*s2)
{
	int count=0;
	int i,j;
	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
			if(s1->arr[i][j]!=s2->arr[i][j])
				count++;
	return count;
}

int mod(int i)
{
	if(i<0)
		return -i;
	else
		return i;
}

int manhattan_heuristic(state *s1, state *s2)
{
	int i,j,m,n;
	int manhat=0;
	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
			{
				for(m=0;m<size;m++)
					for(n=0;n<size;n++)
						if(s1->arr[i][j]==s2->arr[m][n])
							manhat+=mod(i-m)+mod(j-n);
			}
	return manhat;
							
}

void main()
{
	state s1,s2;
	printf("\nEnter state 1: \n");
	inputState(&s1);
	printf("\nEnter state 2: \n");
	inputState(&s2);
	printState(s1);
	printState(s2);
	printf("\nMisplaced Heuristic: %d\n ",misplaced_heuristic(&s1,&s2));
	printf("\nManhattan Heuristic: %d\n ",manhattan_heuristic(&s1,&s2));
}
