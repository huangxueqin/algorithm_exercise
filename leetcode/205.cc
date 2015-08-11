#include "leetc.h"
#include <unordered_map>

using std::unordered_map;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> ccmap;
        unordered_map<char, char> mapped;
        if(s.size() != t.size()) return false;
        int l = s.size();
        for(int i = 0; i < l; i++) {
            char ch1 = s[i];
            char ch2 = t[i];
            if(ccmap.find(ch2) != ccmap.end()) {
                if(ccmap[ch2] != ch1)
                    return false;
            }
            else {
                if(mapped.find(ch1) != mapped.end())
                    return false;
                ccmap[ch2] = ch1;
                mapped[ch1] = ch2;
            }
        }
        return true;
    }
private:
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    cout << sol.isIsomorphic("egg", "add") << endl;
    cout << sol.isIsomorphic("foo", "bar") << endl;
    cout << sol.isIsomorphic("paper", "title") << endl;
    return 0;
}
