#include "binheap.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

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

    Queue->Elements = malloc(sizeof(struct huffman_node*)*(MaxElements+1));
    if(!Queue->Elements) {
        printf("Out of space\n");
        free(Queue);
        return NULL;
    }
    memset(Queue->Elements, 0, sizeof(struct huffman_node*)*(MaxElements+1));

    Queue->Capacity = MaxElements;
    Queue->Size = 0;
    Queue->Elements[0] = malloc(sizeof(struct huffman_node));
    if(!Queue->Elements[0]) {
        return NULL;
    }
    Queue->Elements[0]->c = '-';
    Queue->Elements[0]->count = -1;

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

void Insert(struct huffman_node *x, PriorityQueue Queue)
{
    int i;

    if(IsFull(Queue)) {
        printf("Priority is full\n");
        return;
    }

    if(IsEmpty(Queue)) {
        Queue->Elements[1] = x;
        Queue->Size++;
        return;
    }

    Queue->Size++;
    for(i=Queue->Size; x->count<Queue->Elements[i/2]->count; i/=2) {
        Queue->Elements[i] = Queue->Elements[i/2];
    }

    Queue->Elements[i] = x;
}

struct huffman_node* DeleteMin(PriorityQueue Queue)
{
    int i, Child;
    struct huffman_node *MinElement, *LastElement;

    if(IsEmpty(Queue)) {
        printf("Priority queue is empty\n");
        return Queue->Elements[0];
    }

    MinElement = Queue->Elements[1];
    LastElement = Queue->Elements[Queue->Size];
    Queue->Size--;

    for(i=1; i*2<=Queue->Size; i=Child) {
        Child = i*2;
        if(Child!=Queue->Size && Queue->Elements[Child+1] && Queue->Elements[Child+1]->count<Queue->Elements[Child]->count)
            Child++;//Find the smaller child node that will be the parent node

        if(LastElement->count > Queue->Elements[Child]->count)
            Queue->Elements[i] = Queue->Elements[Child];
        else
            break;//LastElement < Queue->Elements[Child],下滤到最后一层，父节点数值不能大于子节点，把LastElement上升一层成为，叶子的一个父节点
    }

    Queue->Elements[i] = LastElement;

    return MinElement;
}

struct huffman_node* FindMin(PriorityQueue Queue)
{
    return Queue->Elements[1];
}

int IsEmpty(PriorityQueue Queue)
{
    return Queue->Size == 0;
}

int IsFull(PriorityQueue Queue)
{
    return Queue->Size == Queue->Capacity;
}

void PercolateDown(PriorityQueue Queue, int i)
{
    int Child = 0;
    struct huffman_node *tmp = NULL;

    if(!Queue)
        return;

    if(i > Queue->Size || i*2 > Queue->Size)
        return;

    tmp = Queue->Elements[i];
    for(; i<Queue->Size; i=Child) {
        Child = i*2;
        if(Child > Queue->Size)
            break;

        if(Queue->Elements[Child+1]->count < Queue->Elements[Child]->count)
            Child++;

        if(tmp->count > Queue->Elements[Child]->count) {
            Queue->Elements[i] = Queue->Elements[Child];
        } else
            break;
    }

    Queue->Elements[i] = tmp;
}