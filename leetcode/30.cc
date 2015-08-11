#include "leetc.h"
#include <unordered_map>
#include <map>

using std::unordered_map;
using std::map;

class Solution {

public:
    vector<int> findSubstring(string s, vector<string>&words) {
        const int wordLength = words[0].size();
        const int wordNum = words.size();
        map<string, int> wordmap;
        for(int i = 0; i < words.size(); i++) {
            auto it = wordmap.find(words[i]);
            if(it == wordmap.end()) wordmap.insert(std::make_pair(words[i], 1));
            else it->second += 1;
        }
        vector<int> result;
        map<string, int> foundmap;
        for(int i = 0; i < s.size()-wordLength*wordNum+1; i++) {
            foundmap.clear();
            bool ok = true;
            for(int k = 0; k < wordNum; k++) {
                int offset = k*wordLength + i;
                string substring = s.substr(offset, wordLength);
                if(wordmap.find(substring) == wordmap.end()){
                    ok = false;
                    break;
                }
                else {
                    auto it = foundmap.find(substring);
                    if(it == foundmap.end()) foundmap.insert(std::make_pair(substring, 1));
                    else {
                        it->second += 1;
                        if(it->second > wordmap.find(substring)->second) {
                            ok = false;
                            break;
                        }
                    }
                }
            }
            if(ok) {
                result.push_back(i);
            }
        }
        return result;
    }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    string s = "barfoothefoobarman";
    vector<string> words{"foo", "bar"};
    vector<int> indices = sol.findSubstring(s, words);
    for(int i = 0; i < indices.size(); i++) {
        cout << indices[i] << " ";
    }
    cout << endl;
    return 0;
}
