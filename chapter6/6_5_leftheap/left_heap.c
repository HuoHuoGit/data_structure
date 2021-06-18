#include "left_heap.h"
#include <stdlib.h>
#include <stdio.h>

struct TreeNode {
    int Element;
    PriorityQueue Left;
    PriorityQueue Right;
    int Npl;
};

static void SwapChild(PriorityQueue H)
{
    PriorityQueue Tmp;

    Tmp = H->Left;
    H->Left = H->Right;
    H->Right = H->Left;
}

static PriorityQueue Merge1(PriorityQueue H1, PriorityQueue H2)
{
    if(!H1->Left)
        H1->Left = H2;
    else {
        H1->Right = Merge(H1->Right, H2);
        if(H1->Left->Npl < H1->Right->Npl)
            SwapChild(H1);
        H1->Npl = H1->Right->Npl + 1;
    }

    return H1;
}

PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2)
{
    if(!H1)
        return H2;

    if(!H2)
        return H1;

    if(H1->Element < H2->Element)
        return Merge1(H1, H2);
    else
        return Merge1(H2, H1);
}

PriorityQueue Insert1(int X, PriorityQueue H)
{
    PriorityQueue SingleNode;

    SingleNode = malloc(sizeof(struct TreeNode));
    if(!SingleNode) {
        printf("Out of space\n");
        return NULL;
    } else {
        SingleNode->Element = X;
        SingleNode->Npl = 0;
        SingleNode->Left = SingleNode->Right = NULL;
        H = Merge(SingleNode, H);
    }

    return H;
}

PriorityQueue DeleteMin1(PriorityQueue H)
{
    PriorityQueue LeftHeap, RightHeap;

    if(IsEmpaty(H)) {
        printf("Priority queue is empty\n");
        return H;
    }

    LeftHeap = H->Left;
    RightHeap = H->Right;
    free(H);
    return Merge(LeftHeap, RightHeap);
}