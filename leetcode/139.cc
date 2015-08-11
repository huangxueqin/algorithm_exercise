#include "leetc.h"
#include <unordered_set>

using std::unordered_set;

class Solution {
    public:
        bool wordBreak(string s, unordered_set<string> &dict) {
            size_t n = s.size();
            vector<vector<int>> dp(n, vector<int>(n, -1));
            return wordBreak(s, 0, n-1, dict, dp);
        }
    private:
        bool wordBreak(const string &s, const size_t i, const size_t j, 
                const unordered_set<string> &dict, vector<vector<int>> &dp) {
            if(dp[i][j] == -1) {
                for(size_t k = i; k < j; k++) {
                    if(wordBreak(s, i, k, dict, dp) && 
                            wordBreak(s, k+1, j, dict, dp)) {
                        dp[i][j] = 1;
                        break;
                    }
                }
                if(dp[i][j] != 1) {
                    string substr = s.substr(i, j-i+1);
                    dp[i][j] = exist(substr, dict) ? 1 : 0;
                }
            }
            return int2bool(dp[i][j]);
        }
        inline bool int2bool(int i) { return i != 0; }
        inline bool exist(string &s, const unordered_set<string> &dict) {
            return dict.find(s) != dict.end();
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    string s{"leetcode"};
    unordered_set<string> dict{"leet", "code"};
    printf("%s\n", 
            sol.wordBreak(s, dict) ? "true" : "false");
    return 0;
}
