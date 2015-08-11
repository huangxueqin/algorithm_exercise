#include "leetc.h"
#include <algorithm>
#include <unordered_map>

using std::unordered_map;

class Solution {
    private:
        int mark[26];
    public:
        vector<string> anagrams(vector<string> &strs) {
            return sort_anagrams(strs);
        }
    private:
        vector<string> bf_anagrams(const vector<string> &strs) {
            vector<string> result;
            vector<bool> added(strs.size(), false);
            for(size_t i = 0; i < strs.size(); i++) {
                bool found = false;
                if(added[i])
                    continue;
                for(size_t j = i+1; j < strs.size(); j++) {
                    if(added[j])
                        continue;
                    if(is_anagram(strs[i], strs[j])) {
                        result.push_back(strs[j]);
                        found = true;
                        added[j] = true;
                    }
                }
                if(found)
                    result.push_back(strs[i]);
            }
            return result;
        }
        bool is_anagram(const string &s1, const string &s2) {
            if(s1.size() != s2.size()) 
                return false;
            std::memset(mark, 0, 26 * sizeof(int));
            for(size_t i = 0; i < s1.size(); i++)
                ++mark[s1[i]-'a'];
            for(size_t i = 0; i < s2.size(); i++)
                --mark[s2[i]-'a'];
            for(size_t i = 0; i < s2.size(); i++)
                if(mark[s2[i]-'a'] != 0)
                    return false;
            return true;
        }
        vector<string> sort_anagrams(const vector<string> &strs) {
            vector<string> result;
            unordered_map<string, vector<int>> map;
            for(size_t i = 0; i < strs.size(); i++) {
                string str = sort_string(strs[i]);
                auto it = map.find(str);
                if(it == map.end()) {
                    map.insert(std::make_pair(str, vector<int>(1, i)));
                }
                else {
                    it->second.push_back(i);
                }
            }
            for(auto it = map.begin(); it != map.end(); it++) {
                if(it->second.size() > 1)
                    for(size_t i = 0; i < it->second.size(); i++)
                        result.push_back(strs[(it->second)[i]]);
            }
            return result;
        }
        inline string sort_string(string s) {
            std::sort(s.begin(), s.end());
            return s;
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    return 0;
}
