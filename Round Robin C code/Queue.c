#include <stdio.h>
#include <stdlib.h>
#define TYPE process
#include "Queue.h"



node * newNode(TYPE value)
{
    node * n = malloc(sizeof(node));
    n -> value = value;
    n -> next  = NULL;
    return n;
}




void initialize(Queue * s)
{
    //Queue * s;
    //s = (Queue *)malloc(sizeof(Queue));
    s ->front = NULL;
    s->rear = NULL;
    return s;
}


void enqueue( Queue * s, TYPE value)
{

    node * n = newNode(value);
    if(s->front == NULL)
    {
        s->front = n;
        s->rear = n;
    }
    else
    {
        s->rear->next = n;
        s->rear = n;
    }
}

TYPE dequeue( Queue * s)
{
    TYPE value;
    /*if(s->front == NULL)
        return NULL;*/
   // else
    //{
        value = s->front->value;
        node * temp = s->front;
        s->front = s->front->next;
        free(temp);
        if(!s->front)
            s->rear = NULL;
    //}
    return value;
}

int isEmpty( Queue * s)
{
    return s->front == NULL ? 1 : 0 ;
}

