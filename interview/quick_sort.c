#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSERT_SORT_LEN 5

void swap(int i, int j, int *nums) {
    int t = nums[i];
    nums[i] = nums[j];
    nums[j] = t;
}

void insert_sort(const int s, const int e, int *nums) {
    for(int i = s; i <= e; i++) {
        for(int j = i+1; j <= e; j++) {
            if(nums[j] < nums[i])
                swap(i, j, nums);
        }
    }
}

void pivot(const int s, const int e, int *nums) {
    int m = (s+e)/2;
    if(nums[s] > nums[m])
        swap(s, m, nums);
    if(nums[e] > nums[m])
        swap(m, e, nums);
    if(nums[s] > nums[e])
        swap(s, e, nums);
}

void myqsort(const int s, const int e, int *nums) {
    int len = e-s+1;
    if(len < INSERT_SORT_LEN) {
        insert_sort(s, e, nums);
    }
    else {
        pivot(s, e, nums);
        int i = s, j = e-1;
        while(i < j) {
            while(i <= j && nums[i] < nums[e]) ++i;
            while(j >= i && nums[j] > nums[e]) --j;
            swap(i, j, nums);
        }
        swap(j, e, nums);
        myqsort(s, i, nums);
        myqsort(i+1, e, nums);
    }
}

void quick_sort(const int len, int *nums) {
    myqsort(0, len-1, nums);
}

int main(void) {
    int len;
    scanf("%d", &len);
    int *nums = (int *)malloc(sizeof(int) * len);
    for(int i = 0; i < len; i++) {
        scanf("%d", nums+i);
    }
    quick_sort(len, nums);
    for(int i = 0; i < len; i++) {
        printf("%d", nums[i]);
        if(i < len-1) printf(" ");
        else printf("\n");
    }
    return 0;
}
