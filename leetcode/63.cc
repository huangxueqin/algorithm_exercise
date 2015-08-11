#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
            size_t n = obstacleGrid.size();
            size_t m = obstacleGrid[0].size();
            vector<vector<int>> dp(n, vector<int>(m, -1));
            return uniquePathsWithObstacles(obstacleGrid, n-1, m-1, dp);
        }
    private:
        int uniquePathsWithObstacles(const vector<vector<int>> &obs, 
                int i, int j, vector<vector<int>> &dp) {
            if(dp[i][j] == -1) {
                if(i == 0 && j == 0)
                    dp[i][j] = obs[i][j] == 0 ? 1 : 0;
                else {
                    if(i == 0) {
                        dp[i][j] = obs[i][j] == 0 ? uniquePathsWithObstacles(obs, i, j-1, dp) 
                            : 0;
                    }
                    else if(j == 0) {
                        dp[i][j] = obs[i][j] == 0 ? uniquePathsWithObstacles(obs, i-1, j, dp) 
                            : 0;
                    }
                    else {
                        if(obs[i][j] != 0) dp[i][j] = 0;
                        else {
                            dp[i][j] = uniquePathsWithObstacles(obs, i-1, j, dp) + 
                                uniquePathsWithObstacles(obs, i, j-1, dp);
                        }
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
