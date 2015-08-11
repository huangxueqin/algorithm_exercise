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
            if(target < candidates[i]) return;
            else {
                ivec.push_back(candidates[i]);
                if(target-candidates[i] == 0) {
                    result.push_back(ivec);
                    ivec.pop_back();
                    return;
                }
                combinationSum(result, ivec, candidates, i, target-candidates[i]);
                int j = i;
                while(j < candidates.size() && candidates[j] == candidates[i]) j++;
                if(j < candidates.size()) {
                    ivec.pop_back();
                    combinationSum(result, ivec, candidates, j, target);
                }
                else {
                    ivec.pop_back();
                }
            }
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    vector<int> candidates{2,3,6,7};
    int target = 7;
    vector<vector<int>> result = sol.combinationSum(candidates, target);
    print_table(result);
    return 0;
}
