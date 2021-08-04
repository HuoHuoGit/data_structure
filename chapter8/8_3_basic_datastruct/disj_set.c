#include "disj_set.h"
#include <stdio.h>

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

int main(void)
{
    DisjSet s;
    int i = 0;

    Init(s);

    SetUnion(s, 5, 6);
    printf("Find(5) = %d\n", Find(5, s));
    printf("Find(6) = %d\n", Find(6, s));

    for(i=1; i<NUM_SETS+1; i++) {
        printf("%d: %d\t", i, s[i]);
    }
    printf("\n");
}