#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#define SIZE 1000
#define TYPE int


typedef struct
{
    TYPE* items;
    int index;
} Stack;

void initialize(Stack *s);
TYPE pop(Stack * s);
void push(Stack* s, TYPE value);
TYPE top(Stack * s);
int isEmpty(Stack * s);


#endif // STACK_H_INCLUDED
