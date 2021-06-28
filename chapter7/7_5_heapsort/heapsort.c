#include <stdio.h>

#define LEFT_CHILD(i) (2*(i)+1)

void PerDown(int *a, int i, int n)
{
    int child;
    int tmp;

    for(tmp = a[i]; LEFT_CHILD(i)<n; i=child) {
        child = LEFT_CHILD(i);
        if(child!=n-1 && a[child+1]>a[child])
            child++;

        if(tmp < a[child])
            a[i] = a[child];
        else
            break;
    }

    a[i] = tmp;
}

void Swap(int *a, int *b)
{
    int tmp = 0;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void HeapSort(int *a, int size)
{
    int i = 0;

    for(i=size/2; i>=0; i--)
        PerDown(a, i, size);

    for(i=size-1; i>0; i--) {
        Swap(&a[0], &a[i]);
        PerDown(a, 0, i);
    }
}

int main(void)
{
    int a[] = {4, 2, 3, 1, 6, 20, 3, 22};
    int i = 0;

    HeapSort(a, 8);

    for(i=0; i<8; i++) {
        printf("%d\n", a[i]);
    }

    return 0;
}