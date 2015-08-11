#include "leetc.h"

class Solution {
public:
    bool isScramble(string s1, string s2) {
        int n = s1.size();
        if(n == 0) return false;
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(n+1, vector<int>(n+1, -1)));
        return isScramble(s1, s2, 0, 0, n, dp);
    }
private:
    bool isScramble(const string &s1, const string &s2, 
            const int start1, const int start2, const int length, vector<vector<vector<int>>> &dp) {
        if(dp[start1][start2][length] == -1) {
            if(length == 1) {
                dp[start1][start2][length] = s1[start1] == s2[start2] ? 1 : 0;
            }
            else {
                int result = -1;
                for(int i = 1; i < length; i++) {
                    if((isScramble(s1, s2, start1, start2, i, dp) == 1 && 
                                isScramble(s1, s2, start1+i, start2+i, length-i, dp) == 1) 
                            || (isScramble(s1, s2, start1, start2+length-i, i, dp) == 1 && 
                                isScramble(s1, s2, start1+i, start2, length-i, dp) == 1)) {
                        result = 1;
                        break;
                    }
                }
                dp[start1][start2][length] = result == 1 ? 1 : 0;
            }
        }
        return dp[start1][start2][length] == 1;
    }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    return 0;
}
