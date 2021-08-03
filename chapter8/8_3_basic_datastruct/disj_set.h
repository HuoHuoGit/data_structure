#ifndef _DISJ_SET_H_
#define _DISJ_SET_H_

#define NUM_SETS 8

typedef int DisjSet[NUM_SETS+1];
typedef int SetType;
typedef int ElementType;

void Init(DisjSet s);
void SetUnion(DisjSet s, SetType root1, SetType root2);
SetType Find(ElementType x, DisjSet s);

#endif