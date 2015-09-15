#include "leetc.h"
#include <algorithm>

class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> nums(n);
        int i2 = 0, i3 = 0, i5 = 0;
        int next_ugly_num = 1;
        int next_multi_two = 2;
        int next_multi_three = 3;
        int next_multi_five = 5;
        for(int i = 1; i < n; i++) {
            next_ugly_num = std::min(next_multi_two, std::min(next_multi_three, next_multi_five));
            nums[i] = next_ugly_num;
            cout << next_ugly_num << endl;
            if(next_ugly_num == next_multi_two) {
                i2 += 1;
                next_multi_two = nums[i2] * 2;
            }
            if(next_ugly_num == next_multi_three) {
                i3 += 1;
                next_multi_three = nums[i3] * 3;
            }
            if(next_ugly_num == next_multi_five) {
                i5 += 1;
                next_multi_five = nums[i5] * 5;
            }
        }
        return next_ugly_num;
    }
};

Solution sol;

int main(void) {
    cout << sol.nthUglyNumber(10) << endl;
}
