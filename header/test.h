#ifndef _TEST_H_
#define _TEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define rep(n) for(int i = 0; i < (n); i++)

#define input_nums(n, nums) \
    do { \
        rep(n) scanf("%d", (nums)+i);  \
    } \
    while(0)

extern inline void swap(int i, int j, int *nums) {
    int t = nums[i];
    nums[i] = nums[j];
    nums[j] = t;
}

#endif
