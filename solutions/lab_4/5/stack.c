#ifndef STACK
#define STACK

#include "../Base.c"

typedef struct Node
{
    struct Node *next;
    int val;
    char symb;
} Node;

typedef struct Stack
{
    Node *top;
} Stack;

Stack * create_stack()
{
    Stack * s = (Stack *) malloc(sizeof(Stack));
    if (s == NULL){
        return s;
    }
    s->top = NULL;
    return s;
}

void push_back(Stack *to, Node *node)
{
    if (to->top == NULL){
        to->top = node;
        return;
    }
    node->next = to->top;
    to->top = node;
}

Node * stack_pop(Stack *to)
{
    if (to->top == NULL){
        return NULL;
    }
    Node *top = to->top;
    to->top = top->next;
    return top;
}

Node *create_node(int val, char symb)
{
    Node *cur = (Node *) malloc(sizeof(Node));
    if (cur == NULL){
        return NULL;
    }
    cur->val = val;
    cur->symb = symb;
    cur->next = NULL;
    return cur;
}
#endif