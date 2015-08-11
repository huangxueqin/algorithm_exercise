#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        int minPathSum(vector<vector<int>> &grid) {
            size_t n = grid.size();
            size_t m = grid[0].size();
            vector<vector<int>> dp(n, vector<int>(m, -1));
            return minPathSum(grid, n-1, m-1, dp);
        }
    private:
        int minPathSum(const vector<vector<int>> &grid, int i, int j, 
                vector<vector<int>> &dp) {
            if(dp[i][j] == -1) {
                if(i == 0 && j == 0)
                    dp[i][j] = grid[0][0];
                else {
                    if(i == 0) {
                        dp[i][j] = minPathSum(grid, i, j-1, dp) + grid[i][j];
                    }
                    else if(j == 0) {
                        dp[i][j] = minPathSum(grid, i-1, j, dp) + grid[i][j];
                    }
                    else {
                        dp[i][j] = std::min(minPathSum(grid, i-1, j, dp), 
                                minPathSum(grid, i, j-1, dp)) + grid[i][j];
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
