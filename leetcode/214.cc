#include "leetc.h"
#include <algorithm>


class Solution {
public:
    string shortestPalindrome(string s) {
        if(isPalindrome(s)) return s;

        int len = s.size();
        vector<int> pi(len/2, -1);
        int k = -1;
        for(int i = 1; i < pi.size(); i++) {
            while(k >= 0 && s[k+1] != s[i]) k = pi[k];
            if(s[k+1] == s[i]) k++;
            pi[i] = k;
        }

        int i = -1, j = s.size();
        while(i < j) {
            if(s[i+1] == s[j-1]) {
                i++;
                j--;
            }
            else {
                if(i == -1) {
                    j--;
                }
                else {
                    i = pi[i];
                }
            }
        }
        int t = i == j ? 2*i+1 : 2*i;
        string result;
        for(i = s.size()-1; i >= t; i--) {
            result.push_back(s[i]);
        }
        return result + s;
    }
private:
    bool isPalindrome(string s) {
        int i = 0, j = s.size()-1;
        while(i < j && s[i] == s[j]) {
            i++;
            j--;
        }
        return i >= j;
    }
};

Solution sol;

int main(void) {
    string s1 = "aacecaaa";
    string s2 = "abcd";
    cout << s1 << "->" << sol.shortestPalindrome(s1) << endl;
    cout << s2 << "->" << sol.shortestPalindrome(s2) << endl;
    return 0;
}
