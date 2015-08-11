#include <stdio.h>
#include <limits.h>

int maxSubArray(int *nums, int nums_size) {
    int max_sum = INT_MIN;
    int sum = 0;
    int i = 0, j = 0;
    while(j < nums_size) {
        if(i == j || sum > 0) {
            sum += nums[j++];
            if(max_sum < sum)
                max_sum = sum;
        }
        else {
            i = j;
            sum = 0;
        }
    }
    return max_sum;
}
