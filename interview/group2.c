/**
 * group an array of integer by a separator
 * make all elements less than separator reside in the left side
 * and all elements great or equal than separator reside in the right side
 */
#include "../header/test.h"

const int separator = 0;

int group(const int separator, int len, int *nums) {
    int i = 0, j = len-1;
    while(i < j) {
        while(nums[i] <  separator) ++i;
        while(nums[j] >= separator) --j;
        if(i < j) 
            swap(i, j, nums);
    }
    return i;
}

int main(void) {
    int len;
    scanf("%d", &len);
    int *nums = (int *) malloc(sizeof(int) * len);
    input_nums(len, nums);
    group(separator, len, nums);
    for(int i = 0; i < len; i++) {
        printf("%d", nums[i]);
        if(i < len-1) printf(" ");
        else printf("\n");
    }
    return 0;
}
