#include "binheap.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN_PQ_SIZE 10
#define MIN_ELEMENT -1

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

void Destory(PriorityQueue Queue)
{
    free(Queue->Elements);
    free(Queue);
}

void MakeEmpty(PriorityQueue Queue)
{
    Queue->Size = 0;
}

void Insert(int x, PriorityQueue Queue)
{
    int i;

    if(IsFull(Queue)) {
        printf("Priority is full\n");
        return;
    }

    Queue->Size++;
    for(i=Queue->Size; x<Queue->Elements[i/2]; i/=2) {
        Queue->Elements[i] = Queue->Elements[i/2];
    }

    Queue->Elements[i] = x;
}

int DeleteMin(PriorityQueue Queue)
{
    int i, Child;
    int MinElement, LastElement;

    if(IsEmpty(Queue)) {
        printf("Priority queue is empty\n");
        return Queue->Elements[0];
    }

    MinElement = Queue->Elements[1];
    LastElement = Queue->Elements[Queue->Size];
    Queue->Size--;

    for(i=1; i*2<Queue->Size; i=Child) {
        Child = i*2;
        if(Child!=Queue->Size && Queue->Elements[Child+1]<Queue->Elements[Child])
            Child++;//Find the smaller child node that will be the parent node

        if(LastElement > Queue->Elements[Child])
            Queue->Elements[i] = Queue->Elements[Child];
        else
            break;//LastElement < Queue->Elements[Child],下滤到最后一层，父节点数值不能大于子节点，把LastElement上升一层成为，叶子的一个父节点
    }

    Queue->Elements[i] = LastElement;

    return MinElement;
}

int FindMin(PriorityQueue Queue)
{
    return Queue->Elements[1];
}

int IsEmpty(PriorityQueue Queue)
{
    return Queue->Size > 0;
}

int IsFull(PriorityQueue Queue)
{
    return Queue->Size == Queue->Capacity;
}

void PercolateDown(PriorityQueue Queue, int i)
{
    int Child = 0;
    int tmp = 0;

    if(!Queue)
        return;

    if(i > Queue->Size || i*2 > Queue->Size)
        return;

    tmp = Queue->Elements[i];
    for(; i<Queue->Size; i=Child) {
        Child = i*2;
        if(Child < Queue->Size && Queue->Elements[Child+1]<Queue->Elements[Child])
            Child++;

        if(tmp > Queue->Elements[Child]) {
            Queue->Elements[i] = Queue->Elements[Child];
        } else
            break;
    }

    Queue->Elements[i] = tmp;
}