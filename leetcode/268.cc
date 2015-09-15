#include "leetc.h"

class Solution {
public:
    int missingNumber(vector<int> &nums) {
        int i = 0;
        while(i < nums.size()) {
            while(nums[i] != i && nums[i] != nums.size()) {
                int t = nums[i];
                nums[i] = nums[t];
                nums[t] = t;
            }
            i++;
        }
        i = 0;
        while(nums[i] == i) i++;
        return i == nums.size() ? nums.size() : i;
    }
};
