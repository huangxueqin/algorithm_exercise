/*
 * Manacher's Algorithm
 */

#include "leetc.h"

using namespace std;

class Solution {
    public:
        string longestPalindrome(string s) {
            string ss = trans_string(s);
            return manacher_longest_palindrome_substr(ss);
        }
    private:
        string manacher_longest_palindrome_substr(const string &s) {
            int *p = new int[s.size()];
            int max=0, max_p, length = 0, max_length_p = 0;
            for(int i=0;i<s.size();i++) {
                if(i < max) 
                    p[i] = get_min(p[max_p]-(i-max_p), p[2*max_p-i]);
                else
                    p[i] = 1;
                while(i-p[i] >= 0 && i+p[i] < s.size() && s[i+p[i]] == s[i-p[i]])
                    p[i]++;
                if(max < i+p[i]) {
                    max_p = i;
                    max = i+p[i];
                }
                if(length < p[i]) {
                    max_length_p = i;
                    length = p[i];
                }
            }
            delete p;
            string raw_result = s.substr(max_length_p-(length-1), 2*(length-1)+1);
            return reverse_trans_string(raw_result);
        }

        int get_min(int a, int b) {
            return a <= b ? a : b;
        }

        string trans_string(const string &s) {
            string result = "#";
            for(size_t i=0;i<s.size();i++) {
                result += s[i];
                result += "#";
            }
            return result;
        }

        string reverse_trans_string(const string &s) {
            string result = "";
            for(int i=0;i<s.size();i++)
                if(s[i] != '#')
                    result += s[i];
            return result;
        }
};

int main(int argc, char **argv) {
    string pattern = argv[1];
    Solution s;
    cout << s.longestPalindrome(pattern) << endl;
    return 0;
}
