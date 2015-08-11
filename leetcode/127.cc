#include "leetc.h"
#include <unordered_set>
#include <queue>
#include <string>

using namespace std;

class Solution {
    public:
        int ladderLength(string start, string end, unordered_set<string> &dict) {
            std::queue<string> sq;
            sq.push(start);
            sq.push(" ");
            return search(end, sq, dict);
        }
    private:
        int search(const string &end, queue<string> sq, unordered_set<string> &dict) {
            int result = 2;
            while(!sq.empty()) {
                string s = sq.front();
                sq.pop();
                if(s != " ") {
                    for(int i=0;i<s.size();i++) {
                        char tmp = s[i];
                        for(char c='a';c<='z';c++) {
                            if(c == tmp)
                                continue;
                            s[i] = c;
                            if(s == end)
                                return result;
                            if(contains(dict, s)) {
                                sq.push(s);
                                dict.erase(s);
                            }
                        }
                        s[i] = tmp;
                    }
                }
                else {
                    if(!sq.empty()) {
                        result++;
                        sq.push(" ");
                    }
                }
            }
            return 0;
        }
        
        bool contains(unordered_set<string> &dict, string &s) {
            return dict.find(s) != dict.end();
        }

        bool can_translate(const string &s1, const string &s2) {
            int diff_count = 0;
            for(int i=0;i<s1.size();i++) {
                if(s1[i] != s2[i])
                    diff_count++;
                if(diff_count > 1)
                    break;
            }
            return diff_count == 1;
        }
};

int main(void) {
    unordered_set<string> dict = {"rat","pen","pan","pet","pan","pat","ran", "ben"};
    unordered_set<string> dict2 = {"hot", "dog"};
    string start = "rat";
    string end = "ben";
    Solution s;
    cout << s.ladderLength(start, end, dict) << endl;
    return 0;
}
