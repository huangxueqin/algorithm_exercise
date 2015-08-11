#include "leetc.h"

class Solution {
    int digits[9];
    int dp[9][10][9];
public:
    int countDigitOne(int n) {
        if(n < 0) return 0;
        std::memset(dp, -1, sizeof(dp));
        int nb = 0;
        while(n > 0) {
            digits[nb++] = n % 10;
            n /= 10;
        }
        return dfs(nb-1, 0, 0, 1);
    }
private:
    int dfs(int x, int pre, int bo, int limit) {
        if(x < 0) return bo;
        if(!limit && dp[x][pre][bo] != -1) return dp[x][pre][bo];
        int last = limit ? digits[x] : 9;
        int re = 0;
        for(int i = 0; i <= last; i++) {
            re += dfs(x-1, i, i==1 ? bo+1 : bo, limit && (i == last));
        }
        if(!limit) dp[x][pre][bo] = re;
        return re;
    }
};

Solution sol;

int main(void) {
    int n;
    cin >> n;
    cout << sol.countDigitOne(n) << endl;
    return 0;
}
