#ifndef _QUEUE_H_
#define _QUEUE_H_

struct queue;

int is_empty(struct queue *q);
int is_full(struct queue *q);

struct queue* create_queue(int max_elements);
void dispose_queue(struct queue *q);
void make_empty(struct queue *q);

void enqueue(int x, struct queue *q);
int front(struct queue *q);
void dequeue(struct queue *q);
int front_and_dequeue(struct queue *q);

#endif