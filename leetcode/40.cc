#include "leetc.h"
#include <algorithm>

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        vector<vector<int>> combinationSum(vector<int> candidates, int target) {
            std::sort(candidates.begin(), candidates.end());
            vector<vector<int>> result;
            vector<int> ivec;
            combinationSum(result, ivec, candidates, 0, target);
            return result;
        }
    private:
        void combinationSum(vector<vector<int>> &result, vector<int> &ivec, 
                const vector<int> &candidates, int i, int target) {
            if(target < 0) return;
            else if(target == 0) result.push_back(ivec);
            else {
                if(i >= candidates.size()) return;
                int j = i;
                while(j < candidates.size() && candidates[j] == candidates[i]) 
                    j++;
                int cnt = 0;
                int target2 = target;
                while(target2 > 0 && i < j) {
                    ivec.push_back(candidates[i]);
                    target2 -= candidates[i];
                    combinationSum(result, ivec, candidates, j, target2);
                    ++i;
                    ++cnt;
                }
                while(cnt > 0) {
                    ivec.pop_back();
                    cnt--;
                }
                combinationSum(result, ivec, candidates, j, target);
            }
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    vector<int> candidates{10,1,2,7,6,1,5};
    int target = 8;
    vector<vector<int>> result = sol.combinationSum(candidates, target);
    print_table(result);
    return 0;
}
