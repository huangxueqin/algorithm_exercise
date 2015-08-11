#include "leetc.h"
#include <unordered_map>
#include <limits>

using std::unordered_map;

class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> needFound;
        for(int i = 0; i < t.size(); i++) needFound[t[i]]++;
        int begin = 0, foundNum = 0;
        while(begin < s.size() && needFound.find(s[begin]) == needFound.end()) begin++;
        if(begin < s.size()) {
            int minBegin = begin;
            int minLen = std::numeric_limits<int>::max();

            needFound[s[begin]]--;
            foundNum++;
            if(foundNum == t.size()) {
                return s.substr(begin, 1);
            }

            int p = begin+1;
            while(p < s.size()) {
                char ch = s[p];
                if(needFound.find(ch) != needFound.end()) {
                    if(needFound[ch] > 0) 
                        foundNum++;
                    needFound[ch]--;
                    if(ch == s[begin]) {
                        while(needFound.find(s[begin]) == needFound.end() || needFound[s[begin]] < 0) {
                            if(needFound.find(s[begin]) != needFound.end())
                                needFound[s[begin]]++;
                            begin++;
                        }
                    }
                    if(foundNum >= t.size()) {
                        if(minLen > p-begin+1) {
                            minLen = p-begin+1;
                            minBegin = begin;
                        }
                    }
                }
                p++;
            }

            if(foundNum >= t.size()) {
                return s.substr(minBegin, minLen);
            }
        }
        return "";
    }
};
