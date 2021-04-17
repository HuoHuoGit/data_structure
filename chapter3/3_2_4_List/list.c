#include "list.h"
#include <stddef.h> //NULL

struct Node {
    ElementType Element;
    Postion Next;
};

int IsEmpty(List L)
{
    return L->Next == NULL;
}

int IsLast(Postion P, List L)
{
    return P->Next == NULL;
}

Postion Find(ElementType X, List L)
{
    Postion P;

    P = L->Next;
    while (P != NULL && P->Element != X) {
        P = P->Next;
    }

    return P;
}

void Delete(ElementType X, List L)
{
    Postion P, TmpCell;

    P = FindPrevious(X, L);

    if(!IsLast(P, L)) {
        TmpCell = P->Next;
        P->Next = TmpCell->Next;
        free(TmpCell);
    }
}

Postion FindPrevious(ElementType X, List L)
{
    Postion P;

    P = L;
    while (!P->Next && P->Next->Element!=X) {
        P = P->Next;
    }

    return P;
}

void Insert(ElementType X, List L, Postion P)
{
    Postion TmpCell;

    TmpCell = malloc(sizeof(struct Node));
    if(TmpCell == NULL) {
        exit(-1);
    }

    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}

void DeleteList(List L)
{
    Postion P, tmp;

    P = L->Next;

    while (P) {
        tmp = P->Next;
        free(P);
        P = tmp;
    }
}