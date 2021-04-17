#include <stdio.h>

#define SIZE 102400

int MaxSubsequenceSum_1(const int a[], int size)
{
    int ret = a[0];
    int sum = 0;
    int i = 0, j = 0, k = 0;

    for(i=0; i<size; i++) {
        for(j=i; j<size; j++) {
            sum = 0;

            for(k=i; k<=j; k++) {
                sum += a[k];
            }

            if(sum > ret)
                ret = sum;
        }
    }

    return ret;
}

int MaxSubsequenceSum_2(const int a[], int size)
{
    int ret = a[0];
    int sum = 0;
    int i = 0, j = 0;

    for(i=0; i<size; i++) {
        for(j=i; j<size; j++) {
            sum += a[j];

            if(sum > ret)
                ret = sum;
        }
        sum = 0;
    }

    return ret;
}

int max3(int a, int b, int c)
{
    int max = a;
    if(b>max)
        max = b;

    if(c>max)
        max = c;

    return max;
}

int MaxSubsequenceSum_3(const int a[], int left, int right)
{
    int max_left_sum, max_right_sum;
    int max_left_border_sum, max_right_border_sum;
    int left_border_sum, right_border_sum;
    int center, i;

    if(left == right) {
        if(a[left] > 0)
            return a[left];
        else
            return 0;
    }

    center = (left + right) / 2;
    max_left_sum = MaxSubsequenceSum_3(a, left, center);
    max_right_sum = MaxSubsequenceSum_3(a, center+1, right);

    left_border_sum = 0;
    max_left_border_sum = 0;
    for(i=center; i>=left; i--) {
        left_border_sum += a[i];
        if(left_border_sum > max_left_border_sum)
            max_left_border_sum = left_border_sum;
    }

    right_border_sum = 0;
    max_right_border_sum = 0;
    for(i=center+1; i<=right; i++) {
        right_border_sum += a[i];
        if(right_border_sum > max_right_border_sum)
            max_right_border_sum = right_border_sum;
    }

    return max3(max_left_sum, max_right_sum, max_left_border_sum+max_right_border_sum);
}

int MaxSubsequenceSum_4(const int a[], int size)
{
    int sum = 0;
    int ret = 0;
    int i = 0;

    if(!a)
        return 0;

    ret = a[0];

    for(i=0; i<size; i++) {
        sum += a[i];

        if(sum > ret) {
            ret = sum;
        } else if(sum < 0) {
            sum = 0;
        }
    }


    return ret;
}

int main(void)
{
    int a[SIZE] = { 0 };
    int i = 0, j = 0;
    FILE *p = fopen("input", "r");
    if(!p) {
        printf("File \"input\" open error\n");
        return -1;
    }

    for(i=0; i<SIZE; i++) {
        if(fscanf(p, "%d", &a[i]) == -1)
        break;
    }

    for(j=0; j<i; j++) {
        printf("%d ", a[j]);
    }
    printf("\n");

    printf("Test start\n");
    printf("max3(1, 4, 2) = %d\n", max3(1, 4, 1));
    //printf("maxsubsum_1 = %d\n", MaxSubsequenceSum_1(a, SIZE));
    //printf("maxsubsum_2 = %d\n", MaxSubsequenceSum_2(a, SIZE));
    printf("maxsubsum_3 = %d\n", MaxSubsequenceSum_3(a, 0, 6));//SIZE-1));
    //printf("maxsubsum_4 = %d\n", MaxSubsequenceSum_4(a, SIZE));

    fclose(p);

    return 0;
}