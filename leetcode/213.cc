#include "leetc.h"

class Solution {
public:
    int rob(vector<int> &nums) {
        int n = nums.size();
        if(n == 0) return 0;
        vector<int> other1;
        vector<int> other2;
        other1.reserve(nums.size());
        other2.reserve(nums.size());
        for(int i = 1; i < n; i++) {
            other1.push_back(nums[i]);
        }
        for(int i = 2; i < n-1; i++) {
            other2.push_back(nums[i]);
        }
        return std::max(nums[0] + robNonCircular(other2), robNonCircular(other1));
    }
private:
    int robNonCircular(vector<int> &nums) {
        int n = nums.size();
        if(n == 0) return 0;
        else if(n == 1) return nums[0];
        else if(n == 2) return std::max(nums[0], nums[1]);
        else {
            vector<int> dp(n);
            dp[0] = nums[0];
            dp[1] = std::max(nums[0], nums[1]);
            for(int i = 2; i < n; i++) {
                dp[i] = std::max(nums[i] + dp[i-2], dp[i-1]);
            }
            return dp[n-1];
        }
    }
};
