#include<stdio.h>
#include<stdlib.h> //for rand() function
#include<math.h>   // for exp() function


#define INPUT  4
#define LAYER_ONE 12 
#define LAYER_TWO 12
#define OUTPUT 3
#define INPUT_DATA_SIZE 150

int FlowerToValue(char flower[])
{
    if(flower[1] == 'S')
    {
        return 0;
    }

    if(flower[2]=='e')
    {
        return 1;
    }

    return 2;
}

void ValueToFlower(int num)
{
    if(num==0)
    {
    	printf("Setosa");
    }

   	else if(num==1)
   	{
   		printf("Versicolor");
   	}

	else
   	{
   		printf("Virginica");
   	}
}

double sigm(double x)
{
    return 1 / (1 + exp(-x));
}

/*differential of sigm(x) is sigm(x) * (1 - sigm(x))
but the value at a node is already a value sigm from previous layer
we are writing x*(1-x) here */

double dsigm(double x) 
{ 
	return x * (1.00 - x); 
}

double LEARNING_RATE = 0.08;
double input[INPUT_DATA_SIZE][INPUT];
double ACTUAL[INPUT_DATA_SIZE][OUTPUT];
double EXPECTED[INPUT_DATA_SIZE];

double INPUT_LAYER[INPUT];
double LAYER_ONE_ARRAY[LAYER_ONE];
double LAYER_TWO_ARRAY[LAYER_TWO];
double OUTPUT_LAYER[OUTPUT];

double LAYER_ONE_BIAS[LAYER_ONE];
double LAYER_TWO_BIAS[LAYER_TWO];
double OUTPUT_BIAS[OUTPUT];

double INPUT_LAYER_WEIGHTS[INPUT][LAYER_ONE];
double LAYER_ONE_WEIGHTS[LAYER_ONE][LAYER_TWO];
double LAYER_TWO_WEIGHTS[LAYER_TWO][OUTPUT];
double OUTPUT_ERROR_ARRAY[OUTPUT];


//Utility function to read data from the file and store it in an array.
void readFile()
{ 

    FILE *file = fopen("IRIS.csv","r");
    char flower[20];
    for(int i=0;i<INPUT_DATA_SIZE;i++)
    {
	    fscanf(file,"%lf,%lf,%lf,%lf,%[^\n]%*c",&input[i][0],&input[i][1],&input[i][2],&input[i][3],flower);
	    double res;
	    // printf("row = %d %lf %lf %lf %lf %s\n" ,i, input[i][0] , input[i][1],input[i][2],input[i][3],flower);
	    res = FlowerToValue(flower);
	    for(int k = 0;k<OUTPUT;k++)
	    {
	    	ACTUAL[i][k] = 0;
	    }

	    ACTUAL[i][(int)res] = 1;
	    EXPECTED[i] = res;
    }
}

//Utility function to set weights and biases randomly

void randomIntialize()

{ 

	for(int j=0;j<LAYER_ONE;j++)
	{
		LAYER_ONE_BIAS[j] = (rand()%100)/100;

		for(int i=0;i<INPUT;i++)
		{
		    INPUT_LAYER_WEIGHTS[i][j] = ((double)rand())/((double)RAND_MAX);
		}
	}

	for(int j=0;j<LAYER_TWO;j++)
	{
		LAYER_TWO_BIAS[j] = (rand()%100) /100;
		for(int i=0;i<LAYER_ONE;i++)
		{
	        LAYER_ONE_WEIGHTS[i][j] = ((double)rand())/((double)RAND_MAX);
	    }
	}

	for(int j=0;j<OUTPUT;j++)
	{
	    OUTPUT_ERROR_ARRAY[j] = 0;
	    OUTPUT_BIAS[j] = (rand()%100)/100;
	    for(int i=0;i<LAYER_TWO;i++)
	    {
	        LAYER_TWO_WEIGHTS[i][j] = ((double)rand())/((double)RAND_MAX);
	    }
	}
}

void doForwardPropagation(int row)
{
        int i=row;
    
        for(int i=0;i<INPUT;i++)
        {
            INPUT_LAYER[i] = input[row][i];
         
        }     
       
        for(int j = 0;j<LAYER_ONE;j++)
        {
            LAYER_ONE_ARRAY[j] = 0;
            for(int i=0;i<INPUT;i++)
            {
                LAYER_ONE_ARRAY[j] += (INPUT_LAYER_WEIGHTS[i][j] *INPUT_LAYER[i]); 
            }

            LAYER_ONE_ARRAY[j] = sigm(LAYER_ONE_ARRAY[j]);
            
        }
        
        for(int j=0;j<LAYER_TWO;j++)
        {
            LAYER_TWO_ARRAY[j] = 0;
            for(int i=0;i<LAYER_ONE;i++)
            {
                LAYER_TWO_ARRAY[j] += (LAYER_ONE_ARRAY[i] * LAYER_ONE_WEIGHTS[i][j]);
            }

            LAYER_TWO_ARRAY[j] = sigm(LAYER_TWO_ARRAY[j]);
            
        }
        
        for(int j=0;j<OUTPUT;j++)
        {
            OUTPUT_LAYER[j] = 0;
            for(int i=0;i<LAYER_TWO;i++)
            {
                OUTPUT_LAYER[j] += (LAYER_TWO_ARRAY[i] * LAYER_TWO_WEIGHTS[i][j]);
               
            }
            OUTPUT_LAYER[j] = sigm(OUTPUT_LAYER[j]);
            
        } 
       
}

void doBackPropagation(int row)
{
    double deltaOutput[OUTPUT];
    for(int j=0;j<OUTPUT;j++)
    {
    	deltaOutput[j] = (ACTUAL[row][j] - OUTPUT_LAYER[j]) * dsigm(OUTPUT_LAYER[j]);
    }

    double deltaLAYER_TWO_ARRAY[LAYER_TWO];

    for(int j=0;j<LAYER_TWO;j++)
    {
        double curr = 0;
        for(int k=0;k<OUTPUT;k++)
        {
            curr += (deltaOutput[k]*LAYER_TWO_WEIGHTS[j][k]);
        }
        deltaLAYER_TWO_ARRAY[j] = curr * dsigm(LAYER_TWO_ARRAY[j]);
    }

    double deltaLAYER_ONE_ARRAY[LAYER_ONE];

    for(int j=0;j<LAYER_ONE;j++)
    {
        double curr = 0;

        for(int k=0; k<LAYER_TWO; k++)
        	curr += (deltaLAYER_TWO_ARRAY[k] * LAYER_ONE_WEIGHTS[j][k]);
        
        deltaLAYER_ONE_ARRAY[j] = curr * dsigm(LAYER_ONE_ARRAY[j]);
    }

    for(int j=0; j<OUTPUT; j++)
    {
        OUTPUT_BIAS[j] += (LEARNING_RATE * deltaOutput[j]);
        for(int k=0; k<LAYER_TWO; k++)
        {
            LAYER_TWO_WEIGHTS[k][j] += (LAYER_TWO_ARRAY[k]*deltaOutput[j] * LEARNING_RATE);
        }
    }

    for(int j=0;j<LAYER_TWO;j++)
    {
        LAYER_TWO_BIAS[j] += (LEARNING_RATE * deltaLAYER_TWO_ARRAY[j]);
        for(int k=0; k<LAYER_ONE; k++)
        {
            LAYER_ONE_WEIGHTS[k][j] += (LAYER_ONE_ARRAY[k] * deltaLAYER_TWO_ARRAY[j] * LEARNING_RATE );
        }
    }

    for(int j=0;j<LAYER_ONE;j++)
    {
        LAYER_ONE_BIAS[j] += (LEARNING_RATE * deltaLAYER_ONE_ARRAY[j]);
        for(int k=0; k<INPUT; k++)
        {
            INPUT_LAYER_WEIGHTS[k][j] += (input[row][k] *deltaLAYER_ONE_ARRAY[j] *LEARNING_RATE);
        }
    }
}

void trainModel(int n)
{
    for(int t = 0; t<n; t++)
    {
        for(int i=0; i<3; i++)
        {
            for(int j = 0; j<30; j++)
            {
                doForwardPropagation(i*50 + j);
                doBackPropagation(i*50 + j);
            }
        }
    }
}

double doTesting()
{
    printf("EXPECTED\t\tPREDICTED\n---------------------------------------\n\n");
    double correct = 0,total = 0;
    for(int j=0; j<3; j++)
    {
        for(int k=30; k<50; k++)
        {
	        int i = k + j*50;
	        doForwardPropagation(i);
	        total++;
	        int c=0;
	        int max =0;
	        for(int k = 1;k<OUTPUT;k++)
	        {
	            if(OUTPUT_LAYER[max] < OUTPUT_LAYER[k])
	            {
	                max = k;
	            }
	        }

	        ValueToFlower((int)EXPECTED[i]);
	        printf("\t\t\t\t");
	        ValueToFlower((int)max);
	        printf("\n");

	        if(EXPECTED[i] == (double)max)
	        {
	            correct++;
	        }
    	}
    }
    return correct/total;
}

int main()
{
  	readFile();
    randomIntialize();
    // Training Model 1000 times
    trainModel(1000);
    double accuracy = doTesting();
    printf("\nThe accuracy of the model is %lf .\n",accuracy);
    return 0;
}