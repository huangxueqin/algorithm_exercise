#include "leetc.h"

class Solution {
public:
    vector<int> productExceptSelf(vector<int> &nums) {
        vector<int> result(nums.size(), 1);
        for(int i = 0; i < nums.size()-2; i++) {
            result[0] *= nums[i];
            result[i+1] = result[0];
        }
        result[0] = 1;
        for(int i = nums.size()-1; i > 0; i--) {
            result[0] *= nums[i];
            if(i > 1) {
                result[i-1] *= result[0];
            }
        }
        return result;
    }
};

Solution sol;

int main(void) {
    vector<int> nums = {5, 9, 2, -9, -9, -7, -8, 7, -9, 10};
    vector<int> result = sol.productExceptSelf(nums);
    for(int i = 0; i < nums.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    return 0;
}
