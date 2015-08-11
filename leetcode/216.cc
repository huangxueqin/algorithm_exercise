#include "leetc.h"

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> result;
        vector<int> ivec;
        combinationSum3(k, n, 1, result, ivec);
        return result;
    }
    void combinationSum3(int k, int n, int s, vector<vector<int>> &result, vector<int> &ivec) {
        if(k == 0 && n == 0) {
            if(!ivec.empty()) {
                result.push_back(ivec);
            }
        }
        else {
            for(int i = s; i <= 9 && i <= n; i++) {
                ivec.push_back(i);
                combinationSum3(k-1, n-i, i+1, result, ivec);
                ivec.pop_back();
            }
        }
    }
};
