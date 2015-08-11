#include "leetc.h"
#include <algorithm>

class Solution {
public:
    int minDistance(string word1, string word2) {
        int size1 = word1.size();
        int size2 = word2.size();
        if(size1 == 0) {
            return size2;
        }
        if(size2 == 0) {
            return size1;
        }
        vector<vector<int>> dp(size1+10, vector<int>(size2+10, -1));
        return minDistance(word1, word2, 0, 0, dp);
    }
private:
    int minDistance(const string word1, const string word2, 
            const int s1, const int s2, vector<vector<int>> &dp) {
        if(dp[s1][s2] != -1) {
            return dp[s1][s2];
        }
        if(s1 == word1.size() && s2 <= word2.size()) {
            dp[s1][s2] = word2.size() - s2;
        }
        else if(s2 == word2.size() && s1 <= word1.size()) {
            dp[s1][s2] = word1.size() - s1;
        }
        else {
            int dist = minDistance(word1, word2, s1+1, s2+1, dp);
            if(word1[s1] == word2[s2]) {
                dp[s1][s2] = dist;
            }
            else {
                int dist2 = minDistance(word1, word2, s1, s2+1, dp);
                int dist3 = minDistance(word1, word2, s1+1, s2, dp);
                dp[s1][s2] = std::min(dist3, std::min(dist, dist2)) + 1;
            }
        }
        return dp[s1][s2];
    }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    cout << sol.minDistance("a", "a") << endl;
    return 0;
}
