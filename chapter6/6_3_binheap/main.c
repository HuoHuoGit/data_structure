#include <stdio.h>
#include <string.h>
#include "binheap.h"

int main(void)
{
    struct HeapStruct *h = Initialize(15);
    int a[] = {150, 80, 40, 30, 10, 70, 110, 100, 20, 90, 60, 50, 120, 140, 130};
    int i = 0;

    for(i=0; i<15; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");

    memcpy(h->Elements+1, a, 15*sizeof(int));
    h->Size = 15;

    for(i=0; i<15; i++) {
        printf("%d\t", h->Elements[i+1]);
    }
    printf("\n");

    for(i=7; i>0; i--) {
        PercolateDown(h, i);
    }

    for(i=0; i<15; i++) {
        printf("%d\t", h->Elements[i+1]);
    }
    printf("\n");

    return 0;
}