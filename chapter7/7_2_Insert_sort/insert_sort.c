#include <stdio.h>

void InsertionSort(int *a, int size)
{
    int j, p, Tmp;

    for(p=1; p<size; p++) {
        Tmp = a[p];
        for(j=p; j>0&&a[j-1]>Tmp; j--) {
            a[j] = a[j-1];
        }
        a[j] = Tmp;
    }
}

int main(void)
{
    int a[4] = {4, 1, 3, 2};
    int i = 0;

    InsertionSort(a, 4);

    for(i=0; i<4; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}