#include "queue.h"
#include <stdlib.h>

#define MAX_CAPACITY (5)

struct queue {
    int capacity;
    int font;
    int rear;
    int size;
    int *array;
};

int is_empty(struct queue *q)
{
    return q->size == 0;
}

int is_full(struct queue *q)
{
    return q->capacity == q->size;
}

struct queue* create_queue(int max_elements)
{
    struct queue *q = malloc(sizeof(struct queue));
    if(!q)
        return NULL;

    q->capacity = max_elements;
    q->array = malloc(sizeof(int)*max_elements);
    if(!q->array)
        return NULL;

    make_empty(q);

    return q;
}

void dispose_queue(struct queue *q)
{

}

void make_empty(struct queue *q)
{
    q->size = 0;
    q->font = 1;
    q->rear = 0;
}

void enqueue(int x, struct queue *q)
{
    if(is_full(q))
        printf("Queue full\n");
    else {
        q->size++;
        q->rear++;
        if(q->rear == q->capacity)
            q->rear = 0;

        q->array[q->rear] = x;
    }
}

int front(struct queue *q)
{
    if(is_empty(q)) {
        printf("Queue is empty, front error\n");
        return 0;
    }

    return q->array[q->font];
}
void dequeue(struct queue *q)
{
    if(is_empty(q))
        return;

    q->font++;
    if(q->font == q->capacity)
        q->font = 0;
}

int front_and_dequeue(struct queue *q)
{
    int ret = front(q);

    dequeue(q);

    return ret;
}