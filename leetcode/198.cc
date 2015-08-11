#include "leetc.h"
#include <algorithm>

class Solution {
public:
    int rob(vector<int> &nums) {
        int n = nums.size();
        if(n == 0) 
            return 0;
        vector<int> maxProfits(n, -1);
        maxProfits[0] = nums[0];
        if(n >= 2) maxProfits[1] = std::max(nums[0], nums[1]);
        for(int i = 2; i < n; i++)
            maxProfits[i] = std::max(maxProfits[i-1], nums[i] + maxProfits[i-2]);
        return maxProfits[n-1];
    }
private:
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    return 0;
}
