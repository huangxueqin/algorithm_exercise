#include <unordered_map>
#include "leetc.h"

using namespace std;

class Solution {
    public:
        int lengthOfLongestSubstring(string s) {
            return lengthOfLongestSubstring_fast(s);
        }
    private:
        int lengthOfLongestSubstring_fast(const string &s) {
            int Max = 0, current_length = 0;
            size_t p = 0;
            for(size_t i = 0; i < s.size(); i++) {
                char c = s.at(i);
                size_t j = p;
                while(j < i) {
                    if(s.at(j) != c) j++;
                    else break;
                }
                if(j < i) {
                    p = j+1;
                    current_length = i - p + 1;
                }
                else current_length++;
                if(Max < current_length) Max = current_length;
            }
            return Max;
        }
        int lengthOfLongestSubstring_map(const string &s) {
            unordered_map<char, int> char_map;
            int Max = 0, current_length = 0;
            size_t p = 0;
            for(size_t i = 0; i < s.size(); i++) {
                char c = s.at(i);
                auto it = char_map.find(c);
                if(it == char_map.end() || it->second < p) {
                    current_length++;
                }
                else {
                    p = it->second+1;
                    current_length = i - p + 1;
                }
                if(it != char_map.end()) it->second = i;
                else char_map.insert(std::make_pair(c, i));
                if(current_length > Max) Max = current_length;
            }
            return Max;
        }
};

Solution sol;

int main(void) {
    string s = "abcabcbb";
    printf("%d\n", sol.lengthOfLongestSubstring(s));
    return 0;
}
