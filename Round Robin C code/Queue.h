#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#define TYPE process

typedef struct
{
    char name[10];
    int AT, BT;
} process;

typedef struct node
{
    TYPE value;
    struct node * next;
} node;

typedef struct Queue
{
    node *front, *rear;
} Queue;

void initialize(Queue * s);
void enqueue( Queue * s, TYPE value);
TYPE dequeue( Queue * s);
int isEmpty( Queue * s);



#endif // QUEUE_H_INCLUDED
