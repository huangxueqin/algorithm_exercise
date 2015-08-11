#include "cleetc.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

bool containsNearByAlmostDuplicate(int *nums, int nums_size, int k, int t) {
    
}

bool containsNearbyAlmostDuplicate2(int *nums, int nums_size, int k, int t) {
    int i;
    for(i = 0; i < nums_size; i++) {
        int e = min(nums_size-1, i+k);
        for(int j = i+1; j <= e; j++) {
            if(j != i && abs(nums[i] - nums[j]) <= t)
                            return true;
                    }
                }
    return false;
}
