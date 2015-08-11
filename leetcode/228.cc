#include "leetc.h"

class Solution {
public:
    vector<string> summaryRanges(vector<int> &nums) {
        vector<string> ranges;
        int i = 0;
        while(i < nums.size()) {
            int start = nums[i];
            int x = start;
            string range = std::to_string(start);
            while(i+1 < nums.size() && nums[i+1] == x+1) {
                x += 1;
                i += 1;
            }
            i += 1;
            if(x > start) {
                range += "->";
                range += std::to_string(x);
            }
            ranges.push_back(range);
        }
        return ranges;
    }
};
