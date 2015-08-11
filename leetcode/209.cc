#include "leetc.h"

using std::queue;

class Solution {
public:
    int minSubArrayLen(int s, vector<int> &nums) {
        int minLen = nums.size() + 1;
        int sum = 0;
        queue<int> q;
        for(int i = 0; i < nums.size(); i++) {
            q.push(nums[i]);
            sum += nums[i];
            while(sum >= s) {
                int t = q.front();
                if(sum - t < s) {
                    break;
                }
                sum -= t;
                q.pop();
            }
            if(sum >= s) {
                if(q.size() < minLen) {
                    minLen = q.size();
                }
            }
        }
        return minLen > nums.size() ? 0 : minLen;
    }
private:
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int target = 7;
    vector<int> nums{2,3,1,2,4,3};
    Solution sol;
    cout << sol.minSubArrayLen(target, nums) << endl;
    return 0;
}
