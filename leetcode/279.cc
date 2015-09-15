#include "leetc.h"
#include <algorithm>

class Solution {
public:
    int numSquares(int n) {
        vector<int> squareNums;
        int i = 1;
        while(i * i <= n) {
            squareNums.push_back(i * i);
            i++;
        }
        vector<int> dp(n+1, -1);
        return minNum(n, squareNums, dp);
    }
public:
    int minNum(const int n, vector<int> &squareNums, vector<int> &dp) {
        if(n == 0) return 0;
        if(dp[n] == -1) {
            int num = n;
            int i = 0;
            while(i < squareNums.size() && squareNums[i] <= n) {
                num = std::min(num, minNum(n - squareNums[i], squareNums, dp));
                i++;
            }
            dp[n] = num + 1;
        }
        return dp[n];
    }
};

Solution sol;

int main(void) {
    cout << sol.numSquares(12) << endl;
    return 0;
}
