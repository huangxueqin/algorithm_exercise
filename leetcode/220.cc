#include "leetc.h"
#include <unordered_map>
#include <algorithm>

using std::unordered_map;

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
        if(k < 1 || t < 0 || nums.size() <= 1) return false;
        if(t < 1) t = 1;
        unordered_map<long long, long long> iimap;
        for(int i = 0; i < nums.size(); i++) {
            int key = nums[i] / t;
            if((iimap.find(key) != iimap.end() && std::abs(iimap[key] - nums[i]) <= t) || 
                    (iimap.find(key-1) != iimap.end() && std::abs(iimap[key-1] - nums[i]) <= t) ||
                    (iimap.find(key+1) != iimap.end() && std::abs(iimap[key+1] + nums[i]) <= t))
                return true;
            iimap.insert(std::make_pair(key, nums[i]));
            if(i > k) {
                iimap.erase(nums[i-k] / t);
            }
        }
        return false;
    }
};
