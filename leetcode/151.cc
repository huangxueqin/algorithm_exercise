#include "leetc.h"

using namespace std;

class Solution {
    public:
        void reverseWords(string &s) {
            vector<string> svec;
            vector<char> cvec;
            size_t i = 0;
            while(i < s.size()) {
                if(s.at(i) == ' ') {
                    if(!cvec.empty()) {
                        string s;
                        for(auto it = cvec.begin(); it != cvec.end(); it++)
                            s.push_back(*it);
                        svec.push_back(s);
                        cvec.clear();
                    }
                }
                else {
                    cvec.push_back(s.at(i));
                }
                i++;
            }
            if(!cvec.empty()) {
                string s;
                for(auto it = cvec.begin(); it != cvec.end(); it++)
                    s.push_back(*it);
                svec.push_back(s);
                cvec.clear();
            }
            s.clear();
            while(!svec.empty()) {
                s.append(svec.back());
                svec.pop_back();
                if(!svec.empty()) s.push_back(' ');
            }
        }
};

Solution sol;

int main(void) {
    string s = "huang xue qin is a beautiful boy and very clever";
    cout << s << endl;
    sol.reverseWords(s);
    cout << s << endl;
    return 0;
}
