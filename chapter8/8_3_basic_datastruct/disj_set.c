#include "disj_set.h"

void Init(DisjSet s)
{
    int i = 1;

    for(i=1; i<NUM_SETS; i++)
        s[i] = 0;
}

void SetUnion(DisjSet s, SetType root1, SetType root2)
{
    s[root2] = root1;
}

SetType Find(ElementType x, DisjSet s)
{
    if(s[x] <= 0)
        return x;
    else
        return Find(s[x], s);
}