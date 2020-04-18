#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include <string.h>

int evaluatePostfix( char postfix[]);
void infixToPostfix(char infix[], char postfix[]);
int priority (char ch);



int main()
{
    char infix[100];
    char postfix[100];
    int i = 0;
    printf("Please Enter your infix expression:");
    gets(infix);
    infixToPostfix(infix, postfix);
    printf("Your expression in postfix form: ");
    while( postfix[i] != NULL)
    {
        printf("%c", postfix[i]);
        i++;
    }
    printf("\nThe value is %d", evaluatePostfix(postfix));

}





void infixToPostfix(char infix[], char postfix[])
{
    Stack s;
    initialize(&s);
    int i = 0;
    int p = 0;

    while(i < strlen(infix))
    {
        if(infix[i] >= '0' && infix[i] <= '9')
        {
            postfix[p] = infix[i];
            p++;
        }
        else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '/' || infix[i] == '*' || infix[i] == '(' )
        {
            if(isEmpty(&s))
            {
                push(&s, infix[i]);
            }
            else
            {
                while(!isEmpty(&s) && priority(top(&s)) >= priority(infix[i]) && top(&s) != '(' )
                {
                    postfix[p] = pop(&s);
                    p++;
                }
                push(&s, infix[i]);
            }
        }

        else if (infix[i] == ')')
        {
            while(top(&s) != '(')
            {
                postfix[p] = pop(&s);
                p++;
            }
            pop(&s);

        }
        i++;
    }
    while(!isEmpty(&s))
    {
        postfix[p] = pop(&s);
        p++;
    }
    postfix[p] = NULL;
}


int priority (char ch)
{
    switch(ch)
    {
    case '+' :
    case '-' :
        return 1;
    case '*' :
    case '/' :
        return 2;
    case '(' :
        return 9;
    default :
        return -1;
    }
}



int evaluatePostfix( char* postfix)
{
    Stack s;
    initialize(&s);


    int i = 0;
    while(i < strlen(postfix))
    {
        if(postfix[i]>= '0' && postfix[i] <= '9')
        {
            push(&s,postfix[i] - '0');
        }

       // else if (postfix[i] == '0');
        else
        {
            if(postfix[i] == '+')
            {
                push(&s,pop(&s)+ pop(&s));
            }
            else if(postfix[i] == '-')
            {
                int n2 = pop(&s);
                int n1 = pop(&s);
                push(&s,n1 - n2);

            }
            else if(postfix[i] == '*')
            {
                push(&s,pop(&s)* pop(&s));

            }
            else if(postfix[i] == '/')
            {
                int n2 = pop(&s);
                int n1 = pop(&s);
                push(&s,n1 / n2);
            }

            // printf("in %d\n",i);

        }
        i++;
    }

    return pop(&s);
}
