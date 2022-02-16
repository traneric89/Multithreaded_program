/* Including neccessary headers */

#include <pthread.h>
#include <stdio.h>

//Declaring Global variables

int avg=0;
int len;
int minValue=0;
int maxValue=0;



/* Function to calculate average */

void *calcAvg(void *arg)
{
    int i = 0, sum = 0;
    int *numberArray;

    //Fetching array
    numberArray = (int*)arg;

    //Iterating over the entire length of array
    for(i=0; i<len; i++)
    {
        //Adding all numbers in array to get total sum
        sum = sum + numberArray[i];
    }

    //Calculating the average
    avg = sum / len;

    return NULL;
}

/* Function to find min value */


void *calcMin(void *arg)
{
    int i = 0;
    int *numberArray;

    //Fetching array
    numberArray = (int*)arg;

    //Initializing minimum value as starting element
    minValue = numberArray[0];

    //Iterating over array
    for(i=0; i<len; i++)
    {
        //Comparing value
        if(numberArray[i] < minValue)  
        {
            //Updating minimum value
            minValue = numberArray[i];
        }
    }

    return NULL;
}

/* Function to find max value */
void *calcMax(void *arg)
{
    int i = 0;
    int *numberArray;

    //Fetching array
    numberArray = (int*)arg;

    //Initializing maximum value as starting element
    maxValue = numberArray[0];

    //Iterating over array
    for(i=0; i<len; i++)
    {
        //Comparing value
        if(numberArray[i] > maxValue)  
        {
            //Updating maximum value
            maxValue = numberArray[i];
        }
    }

    return NULL;
}

/* Main function */


int main(void)
{
    //Thread identifiers
    pthread_t avgPth, minPth, maxPth;  
    int i = 0;

    //Get how many numbers user plans on inputting
    int amount;
    
    printf("Enter how many numbers you will input:");
    scanf("%d", &amount);
    
    //Creating array of size of amount of numbers using plans on inputting
    int values[amount];
    len = amount;
    
    //Iterating through to place inputted numbers in values array 
    for(int counter=0; counter<amount; counter++){
        scanf("%d", &values[counter]);
    }

    //Creating three threads one for each operation
    pthread_create(&avgPth, NULL, calcAvg, values);
    pthread_create(&minPth, NULL, calcMin, values);
    pthread_create(&maxPth, NULL, calcMax, values);
  
    //Waiting till all threads finish their work
    pthread_join(avgPth,NULL);
    pthread_join(minPth,NULL);
    pthread_join(maxPth,NULL);
  
    //Printing results
    printf(" Average = %d ", avg);
    printf(" Minimum = %d ", minValue);
    printf(" Maximum = %d ", maxValue);

    return 0;
}
