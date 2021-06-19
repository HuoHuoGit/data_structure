#include <stdio.h>

#define MAX_TREES 100

typedef struct BinNode *Position;
typedef struct BinNode *BinTree;
typedef struct Colletcion *BinQueue;

struct BinNode {
    int Element;
    Position LeftChild;
    Position NextSibiling;
};

struct Colletcion {
    int CurrentSize;
    BinTree TheTrees[MAX_TREES];
};

BinTree CombineTrees(BinTree T1, BinTree T2)
{
    if(T1->Element > T2->Element)
        return CombineTrees(T2, T1);

    T2->NextSibiling = T1->LeftChild;
    T1->LeftChild = T2;

    return T1;
}

BinQueue Merge(BinQueue H1, BinQueue H2)
{
    BinTree T1, T2, Carry = NULL;
    int i, j;

#if 0//Capacity is undefined.
    if(H1->CurrentSize+H2->CurrentSize > Capacity) {
        printf("Merge would exceed capcity\n");
        return NULL;
    }
#endif

    H1->CurrentSize += H2->CurrentSize;
    for(i=0, j=0; j<=H1->CurrentSize; i++, j*=2) {
        T1 = H1->TheTrees[i];
        T2 = H2->TheTrees[i];

        switch (!!T1 + 2*(!!T2) + 4*(!!Carry)) {
            case 0:
            case 1:
                break;

            case 2:
                H1->TheTrees[i] = T2;
                H2->TheTrees[i] = NULL;
                break;

            case 4:
                H1->TheTrees[i] = Carry;
                Carry = NULL;
                break;

            case 3:
                Carry = CombineTrees(T1, T2);
                H1->TheTrees[i] = H2->TheTrees[i] = NULL;
                break;

            case 5:
                Carry = CombineTrees(T1, Carry);
                H1->TheTrees[i] = NULL;
                break;

            case 6:
                Carry = CombineTrees(T2, Carry);
                H2->TheTrees[i] = NULL;
                break;

            case 7:
                H1->TheTrees[i] = Carry;
                Carry = CombineTrees(T1, T2);
                H2->TheTrees[i] = NULL;
                break;

            default:
                break;
        }
    }

    return H1;
}

static int IsEmpty(BinQueue H);

#define INFINITY 0xFFFFFFFFFFFFFFFF
int DeleteMin(BinQueue H)
{
    int i, j;
    int MinTree;
    BinQueue DeletedQueue;
    Position DeletedTree, OldRoot;
    int MintItem;

    if(IsEmpty(H)) {
        printf("Empty binomial queue\n");
        return -1;
    }

    MintItem = INFINITY;
    for(i=0; i<MAX_TREES; i++) {
        if(H->TheTrees[i] && H->TheTrees[i]->Element < MintItem) {
            MintItem = H->TheTrees[i]->Element;
            MinTree = i;
        }
    }

    DeletedTree = H->TheTrees[MinTree];
    OldRoot = DeletedTree;
    DeletedTree = DeletedTree->LeftChild;
    free(OldRoot);

    DeletedQueue = Initialize();
    DeletedQueue->CurrentSize = (1 << MinTree) - 1;
    for(j=MinTree-1; j>=0; j--) {
        DeletedQueue->TheTrees[j] = DeletedTree;
        DeletedTree = DeletedTree->NextSibiling;
        DeletedQueue->TheTrees[j]->NextSibiling = NULL;
    }

    H->TheTrees[MinTree] = NULL;
    H->CurrentSize -= DeletedQueue->CurrentSize + 1;

    Merge(H, DeletedQueue);
    return MinTree;
}