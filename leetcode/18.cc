/*
 * n sum prob.
 */
#include "leetc.h"
#include <algorithm>

using namespace std;

class Solution {
    public:
        vector<vector<int>> fourSum(vector<int> &num, int target) {
            vector<vector<int>> result;
            std::sort(num.begin(), num.end());
            vector<int> ivec;
            for(size_t i=0;i+3 < num.size();i++) {
                ivec.push_back(num[i]);
                three_sum(result, ivec, num, i+1, target-num[i]);
                ivec.pop_back();
                while(i+3 < num.size() && num[i+1] == num[i]) i++;
            }
            return result;
        }
    private:
        void three_sum(vector<vector<int>> &result, vector<int> &ivec, 
                vector<int> &num, int start, int target){
            for(size_t i=start;i+2<num.size();i++) {
                ivec.push_back(num[i]);
                int tmp_target = target-num[i];
                int j = i+1, k = num.size()-1;
                while(j < k) {
                    int sum = num[j] + num[k];
                    if(sum < tmp_target) j++;
                    else if(sum > tmp_target) k--;
                    else {
                        ivec.push_back(num[j]);
                        ivec.push_back(num[k]);
                        if(result.empty() || !std::equal(ivec.begin(), ivec.end(), result.back().begin()))
                            result.push_back(ivec);
                        ivec.pop_back();
                        ivec.pop_back();
                        j++;
                        k--;
                    }
                }
                ivec.pop_back();
                while(i+2 < num.size() && num[i+1] == num[i]) i++;
            }
        }
};

int main(void) {
    vector<int> num;
    Solution s;
    print_table(s.fourSum(num, 0));
    return 0;
}
