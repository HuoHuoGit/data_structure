#include <stdio.h>
#include <stdlib.h>

void Merge(int a[], int tmp_array[], int l_pos, int r_pos, int right_end)
{
    int i, left_end, num_elements, tmp_pos;

    left_end = r_pos - 1;
    tmp_pos = l_pos;
    num_elements = right_end - l_pos + 1;

    while(l_pos<=left_end && r_pos<=right_end) {
        if(a[l_pos] < a[r_pos]) {
            tmp_array[tmp_pos] = a[l_pos];
            tmp_pos++;
            l_pos++;
        } else {
            tmp_array[tmp_pos] = a[r_pos];
            tmp_pos++;
            r_pos++;
        }
    }

    while(l_pos <= left_end) {
        tmp_array[tmp_pos] = a[l_pos];
        tmp_pos++;
        l_pos++;
    }

    while(r_pos <= right_end) {
        tmp_array[tmp_pos] = a[r_pos];
        tmp_pos++;
        r_pos++;
    }

    //因为l_pos被破坏，无法记录数组的开始位置，所以要倒序复制
    for(i=0; i<num_elements; i++, right_end--) {
        a[right_end] = tmp_array[right_end];
    }
}

void MSort(int a[], int tmp_array[], int left, int right)
{
    int center;

    if(left < right) {
        center = (left + right) / 2;
        MSort(a, tmp_array, left, center);
        MSort(a, tmp_array, center+1, right);
        Merge(a, tmp_array, left, center+1, right);
    }
}

void MergeSort(int a[], int len)
{
    int *tmp_array = NULL;

    tmp_array = (int *)malloc(sizeof(int)*len);
    if(!tmp_array) {
        printf("Out of space\n");
        return;
    }

    MSort(a, tmp_array, 0, len-1);
    free(tmp_array);
}

int main(void)
{
    int a[] = {54, 23, 1, 44, 2341, 12341, 33, 55};
    int i = 0;

    MergeSort(a, 8);

    for(i=0; i<8; i++) {
        printf("%d\n", a[i]);
    }

    return 0;
}