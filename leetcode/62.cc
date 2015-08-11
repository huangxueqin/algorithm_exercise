#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        int uniquePaths(int m, int n) {
            vector<vector<int>> dp(n, vector<int>(m, -1));
            return uniquePaths(n-1, m-1, dp);
        }
    private:
        int uniquePaths(int i, int j, vector<vector<int>> &dp) {
            if(dp[i][j] == -1) {
                if(i == 0 && j == 0)
                    dp[i][j] = 1;
                else {
                    if(i == 0) {
                        dp[i][j] = uniquePaths(i, j-1, dp);
                    }
                    else if(j == 0) {
                        dp[i][j] = uniquePaths(i-1, j, dp);
                    }
                    else {
                        dp[i][j] = uniquePaths(i-1, j, dp) + uniquePaths(i, j-1, dp);
                    }
                }
            }
            return dp[i][j];
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    return 0;
}
