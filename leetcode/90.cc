#include "leetc.h"  
#include <algorithm>

using std::vector;
using std::string;

class Solution {
    public:
        vector<vector<int>> subsetsWithDup(vector<int> &s) {
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
            size_t nextp = start+1;
            while(nextp < s.size() && s[nextp] == s[start]) nextp++;
            size_t cnt = nextp - start;
            for(size_t i = 0; i < cnt; i++) {
                ivec.push_back(s[start]);
                result.push_back(ivec);
                get_subset_start_with(s, nextp, result, ivec);
            }
            for(size_t i = 0; i < cnt; i++) {
                ivec.pop_back();
            }
            get_subset_start_with(s, nextp, result, ivec);
        }
};

Solution sol;

int main(void) {
    printf("----------Test----------\n");
    int arr[] = {1, 2, 3};
    vector<int> s(arr, arr+3);
    vector<vector<int>> subsets = sol.subsetsWithDup(s);
    std::printf("table size = %zu\n", subsets.size());
    print_table(subsets);
    return 0;
}
