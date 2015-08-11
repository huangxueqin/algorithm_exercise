#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        vector<vector<int>> combine(int n, int k) {
            vector<vector<int>> result;
            vector<int> ivec;
            if(n < k) return result;
            combine(n, k, 0, 1, result, ivec);
            return result;
        }
    private:
        void combine(const int n, const int k, const int c, const int s, 
                vector<vector<int>> &result, vector<int> &ivec) {
            if(c == k) {
                result.push_back(ivec);
                return;
            }
            for(int i = s; i <= n-k+c+1; i++) {
                ivec.push_back(i);
                combine(n, k, c+1, i+1, result, ivec);
                ivec.pop_back();
            }
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int n = 4, k = 2;
    vector<vector<int>> result = sol.combine(n, k);
    print_table(result);
    return 0;
}
