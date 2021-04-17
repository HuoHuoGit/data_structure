#ifndef _STACK_H_
#define _STACK_H_

/*
stack的实现为先创建head，head不变，head->next为栈顶
*/

struct stack;

int is_empty(struct stack *s);
struct stack *create_stack(void);
void dispose_stack(struct stack *s);
void make_empty(struct stack *s);
void push(int x, struct stack *s);
int top(struct stack *s);
void pop(struct stack *s);

#endif