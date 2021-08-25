#ifndef _BINHEAP_H_
#define _BINHEAP_H_
#include "huffman.h"

struct HeapStruct {
    int Capacity;
    int Size;
    struct huffman_node **Elements;
};

typedef struct HeapStruct *PriorityQueue;

PriorityQueue Initialize(int max_elements);
void Destory(PriorityQueue Queue);
void MakeEmpty(PriorityQueue Queue);
void Insert(struct huffman_node *x, PriorityQueue Queue);
struct huffman_node* DeleteMin(PriorityQueue Queue);
struct huffman_node* FindMin(PriorityQueue Queue);
int IsEmpty(PriorityQueue Queue);
int IsFull(PriorityQueue Queue);
void PercolateDown(PriorityQueue Queue, int i);

#endif