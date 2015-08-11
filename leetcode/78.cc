#include "leetc.h"
#include <algorithm>

using std::vector;
using std::string;

class Solution {
public:
        vector<vector<int>> subsets(vector<int> &s) {
            std::sort(s.begin(), s.end());
            vector<vector<int>> result;
            vector<int> ivec;
            get_subset_start_with(s, 0, result, ivec);
            return result;
        }
    private:
        void get_subset_start_with(const vector<int> &s, const size_t start, 
                vector<vector<int>> &result, vector<int> &ivec) {
            if(start == s.size()) {
                return;
            }
            if(start == 0)
                result.push_back(ivec);
            get_subset_start_with(s, start+1, result, ivec);
            ivec.push_back(s[start]);
            result.push_back(ivec);
            get_subset_start_with(s, start+1, result, ivec);
            ivec.pop_back();
        }
};

Solution sol;

int main(void) {
    printf("----------Test----------\n");
    int arr[] = {1, 2};
    vector<int> s(arr, arr+2);
    vector<vector<int>> subsets = sol.subsets(s);
    std::printf("table size = %zu\n", subsets.size());
    print_table(subsets);
    return 0;
}
