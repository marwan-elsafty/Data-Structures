#include <stdio.h>
#include "Stack.h"
#include <stdlib.h>
#define SIZE 1000
#define TYPE int



void initialize(Stack *s)
{
    s->index = 0;
    s->items = (TYPE *)malloc(SIZE* sizeof(TYPE));
}

TYPE pop(Stack * s)
{
    return s->items[--s->index];
}

void push(Stack* s, TYPE value)
{
    s->items[s->index++] = value;

}

TYPE top(Stack * s)
{
    TYPE x = pop(s);
    push(s,x);
    return x;
}

int isEmpty(Stack * s)
{
    return s->index == 0 ? 1 : 0;
}


