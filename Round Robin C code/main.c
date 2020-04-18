#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include <string.h>

//A defined structures containing the process' name, arrival time and burst time
// Already defined in the header file

/*
* typedef struct
*  {
*    char name[10];
*    int AT, BT;
*  } process;
*/

//PROTOTYPES
int readFile(FILE * fr, process processes[], int *slots);
void checkAT(process processes[], int length, Queue *mainQ, int i);
void checkBT(process x, Queue * mainQ);
void RoundRobin( process processes[], int *slots, int length);


// Function to read from files
int readFile(FILE * fr, process processes[], int *slots)
{
    int i = 0;
    //Read watching time slots
    fscanf(fr, "%d", slots);

    //Read the process' name, its arrival time and its burst time
    while(!feof(fr))
    {
        fscanf(fr, "%s %d %d", processes[i].name,&processes[i].AT, &processes[i].BT);
        i++;
    }


    return i; // return the number of processes
}


//Function to check Arrival time
void checkAT(process processes[], int length, Queue *mainQ, int i)
{
    int j;
    for(j=0 ; j < length ; j++ )
    {
        if(processes[j].AT == i)
            enqueue(mainQ, processes[j]);
    }
}



//Function to check Burst time
void checkBT(process x, Queue * mainQ)
{
    if(x.BT == 0)
        //if time required in processor is finished the process aborts
        printf("%s aborts",x.name);
    else
        //if not it is resent to the end of the queue
        enqueue(mainQ, x);
}




//Round Robin scheduling function
void RoundRobin( process processes[], int *slots, int length)
{
    Queue mainQ ;
     initialize(&mainQ);
    int i;

    checkAT(processes, length, &mainQ, 0);

    for(i=0 ; i < *slots ; i++)
    {

        if(isEmpty(&mainQ))
        {
            printf("idle\t(%d-->%d)\n",i,i+1);
            checkAT(processes, length, &mainQ, i+1);

        }
        else
        {
            process x = dequeue(&mainQ);
            printf("%s\t(%d-->%d)",x.name, i, i+1 );
            x.BT--;

            checkAT(processes, length, &mainQ, i+1);
            checkBT(x, &mainQ);
            printf("\n");
        }

    }
    printf("Stop");
}

int main()
{
    FILE * fr = fopen("process.txt", "r");
    process processes[100];
    int slots;
    int length;

    //Read processes and return its number
    length = readFile(fr, processes, &slots);
    //scheduling the processes
    RoundRobin(processes, &slots, length);


    return  0;
}




