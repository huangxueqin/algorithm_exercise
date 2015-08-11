#include "leetc.h"
#include <stack>

using std::stack;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        vector<int> result;
        if(nums.size() > 0) {
            vector<int> fwrd(nums.size(), -1);
            stack<int> istk;
            for(int i = 0; i < nums.size(); i++) {
                int t = nums[i];
                while(!istk.empty() && t >= nums[istk.top()]) {
                    int num = istk.top(); istk.pop();
                    fwrd[num] = i;
                }
                istk.push(i);
            }

            int maxi = -1;
            for(int i = 0; i <= nums.size()-k; i++) {
                if(maxi < i) {
                    maxi = i;
                }
                while(fwrd[maxi] >= 0 && fwrd[maxi] < i+k) maxi = fwrd[maxi];
                result.push_back(nums[maxi]);
            }
        }
        return result;
    }
};
