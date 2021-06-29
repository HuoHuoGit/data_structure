#ifndef _BINHEAP_H_
#define _BINHEAP_H_

struct HeapStruct {
    int Capacity;
    int Size;
    int *Elements;
};

typedef struct HeapStruct *PriorityQueue;

PriorityQueue Initialize(int max_elements);
void Destory(PriorityQueue Queue);
void MakeEmpty(PriorityQueue Queue);
void Insert(int x, PriorityQueue Queue);
int DeleteMin(PriorityQueue Queue);
int FindMin(PriorityQueue Queue);
int IsEmpty(PriorityQueue Queue);
int IsFull(PriorityQueue Queue);
void PercolateDown(PriorityQueue Queue, int i);

#endif