#ifndef STACK
#define STACK

#include "../Base.c"

typedef struct Node
{
    struct Node *next;
    char *symb;
} Node;

typedef struct Stack
{
    Node *top;
} Stack;

Stack *create_stack()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (s == NULL)
    {
        return s;
    }
    s->top = NULL;
    return s;
}

void push_back(Stack *to, Node *node)
{
    if (to->top == NULL)
    {
        to->top = node;
        return;
    }
    node->next = to->top;
    to->top = node;
}

Node *stack_pop(Stack *to)
{
    if (to->top == NULL)
    {
        return NULL;
    }
    Node *top = to->top;
    to->top = top->next;
    return top;
}

Node *create_node(char* symb)
{
    Node *cur = (Node *)malloc(sizeof(Node));
    if (cur == NULL)
    {
        return NULL;
    }
    cur->symb = symb;
    cur->next = NULL;
    return cur;
}
void delete_node(Node *nd){
    //free(nd->symb);
    free(nd);
}

void delete_stack(Stack **stack)
{
    Node *cur;
    while ((cur = stack_pop(*stack)) != NULL)
    {
        delete_node(cur);
    }
    free(*stack);
    *stack = NULL;
}
#endif