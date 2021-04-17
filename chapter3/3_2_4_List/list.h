#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>

#define ElementType int

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Postion;

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Postion P, List L);
Postion Find(ElementType X, List L);
void Delete(ElementType X, List L);
Postion FindPrevious(ElementType X, List L);
void Insert(ElementType X, List L, Postion P);
void DeleteList(List L);
Postion Header(List L);
Postion First(List L);
Postion Advance(Postion P);
ElementType Retrieve(Postion P);

#endif