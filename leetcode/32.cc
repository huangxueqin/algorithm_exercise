#include "leetc.h"
#include <stack>

using std::stack;

class Solution {
public:
    int longestValidParentheses(string s) {
        vector<std::pair<int, int>> matches;
        stack<int> cs;
        int i = 0; 
        while(i < s.size()) {
            char c = s[i];
            if(c == '(') {
                cs.push(i);
            }
            else {
                if(!cs.empty()) {
                    int start = cs.top();
                    cs.pop();
                    mergeMatches(matches, std::make_pair(start, i));
                }
            }
            i++;
        }
        int maxLen = 0;
        for(int k = 0; k < matches.size(); k++) {
            if(matches[k].second-matches[k].first+1 > maxLen) {
                maxLen = matches[k].second - matches[k].first + 1;
            }
        }
        return maxLen;
    }
private:
    void mergeMatches(vector<std::pair<int, int>> &matches, std::pair<int, int> newMatch) {
        if(matches.empty()) {
            matches.push_back(newMatch);
        }
        else {
            std::pair<int, int> lastMatch = matches.back();
            if(lastMatch.second+1 < newMatch.first) {
                matches.push_back(newMatch);
            }
            else if(lastMatch.second+1 == newMatch.first) {
                newMatch.first = lastMatch.first;
                matches.pop_back();
                mergeMatches(matches, newMatch);
            }
            else {
                matches.pop_back();
                mergeMatches(matches, newMatch);
            }
        }
    }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    return 0;
}
