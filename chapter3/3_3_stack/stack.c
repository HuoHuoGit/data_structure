#include "stack.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct stack {
    int element;
    struct stack *next;
};


int is_empty(struct stack *s)
{
    return s->next == NULL;
}

struct stack *create_stack(void)
{
    struct stack *s = NULL;

    s = malloc(sizeof(struct stack));
    if(!s) {
        printf("No memory\n");
        return NULL;
    }
    s->next = NULL;
    make_empty(s);

    return s;
}
void dispose_stack(struct stack *s)
{
    make_empty(s);
    free(s);
}
void make_empty(struct stack *s)
{
    if(s == NULL) {
        printf("Must create stack first\n");
        return;
    }
    while (!is_empty(s))
        pop(s);
}

void push(int x, struct stack *s)
{
    struct stack *tmp = NULL;

    tmp = malloc(sizeof(struct stack));
    if(!tmp) {
        printf("No memory\n");
        return NULL;
    }
    tmp->element = x;
    tmp->next = s->next;
    s->next = tmp;
}
int top(struct stack *s)
{
    if(is_empty(s))
        return 0;

    return s->next->element;
}
void pop(struct stack *s)
{
    struct stack *tmp = NULL;
    if(is_empty(s))
        return;

    tmp = s->next->next;
    free(s->next);
    s->next = tmp;
}