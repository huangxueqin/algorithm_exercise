#include "leetc.h"
#include <algorithm>

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.size();
        int n2 = s2.size();
        int n3 = s3.size();
        if(n1+n2 != n3) return false;
        vector<vector<int>> dp(n1+1, vector<int>(n2+1, -1));
        return isInterleave(s1, s2, s3, 0, 0, 0, dp) || (dp = vector<vector<int>>(n1+1, vector<int>(n2+1, -1)), 
            isInterleave(s1, s2, s3, 0, 0, 1, dp));
    }
private:
    bool isInterleave(const string &s1, const string &s2, const string s3, 
            const int p1, const int p2, const int lead, vector<vector<int>> &dp) {
        if(p1 >= s1.size() && p2 >= s2.size()) {
            return true;
        }
        if(dp[p1][p2] == -1) {
            int offset = p1 + p2;
            if(lead == 0) {
                int p = p1;
                while(p < s1.size() && s1[p] == s3[offset]) {
                    p++;
                    if(isInterleave(s1, s2, s3, p, p2, 1, dp)) {
                        dp[p1][p2] = 1;
                        break;
                    }
                    offset++;
                }
            }
            else {
                int p = p2;
                while(p < s2.size() && s2[p] == s3[offset]) {
                    p++;
                    if(isInterleave(s1, s2, s3, p1, p, 0, dp)) {
                        dp[p1][p2] = 1;
                        break;
                    }
                    offset++;
                }
            }
            if(dp[p1][p2] == -1)
                dp[p1][p2] = 0;
        }
        return dp[p1][p2] == 1;
    }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    return 0;
}
