#include "leetc.h"

using namespace std;

class Solution {
    public:
        int numTrees(int n) {
            vector<vector<int>> dp = init_dp_table(n);
            return compute_num_trees(0, n-1, dp);
        }
    private:
        int compute_num_trees(int i, int j, vector<vector<int>> &dp) {
            if(i > j) return 1;
            if(dp[i][j] == -1) {
                int result = 0;
                for(int k = i; k <= j; k++) {
                    result += compute_num_trees(i, k-1, dp) *
                        compute_num_trees(k+1, j, dp);
                }
                dp[i][j] = result;
            }
            return dp[i][j]; 
        }

        vector<vector<int>> init_dp_table(int n) {
            vector<vector<int>> dp;
            for(int i = 0; i < n; i++) {
                dp.push_back(vector<int>(n, -1));
            }
            return dp;
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("more param");
        return 0;
    }
    int n = std::atoi(argv[1]);
    printf("%d\n",sol.numTrees(n));
    return 0;
}
