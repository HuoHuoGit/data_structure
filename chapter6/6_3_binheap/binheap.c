#include "binheap.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN_PQ_SIZE 20
#define MIN_ELEMENT -1

struct HeapStruct {
    int Capacity;
    int Size;
    int *Elements;
};

PriorityQueue Initialize(int MaxElements)
{
    PriorityQueue Queue;

    if(MaxElements < MIN_PQ_SIZE) {
        printf("Priority queue size is too small\n");
        return NULL;
    }

    Queue = malloc(sizeof(struct HeapStruct));
    if(!Queue) {
        printf("Out of space\n");
        return NULL;
    }

    Queue->Elements = malloc(sizeof(int)*(MaxElements+1));
    if(!Queue->Elements) {
        printf("Out of space\n");
        free(Queue);
        return NULL;
    }

    Queue->Capacity = MaxElements;
    Queue->Size = 0;
    Queue->Elements[0] = MIN_ELEMENT;

    return Queue;
}

void Insert(int x, PriorityQueue Queue)
{
    int i;

    if(IsFull(Queue)) {
        printf("Priority is full\n");
        return;
    }

    for(i=Queue->Size; Queue->Elements[i/2]>x; i/=2) {
        Queue->Elements[i] = Queue->Elements[i/2];
    }

    Queue->Elements[i] = x;
}