#include "leetc.h"

class Solution {
public:
    vector<string> fullJustify(vector<string> &words, int maxWidth) {
        int pos = 0;
        vector<string> result;
        while(pos < words.size()) {
            int start = pos;
            int length = words[pos++].size();
            int numWords = 1;
            while(pos < words.size() &&
                    length+1+words[pos].size() <= maxWidth) {
                length += 1 + words[pos].size();
                numWords += 1;
                pos += 1;
            }
            string s = "";
            if(numWords == 1 || pos >= words.size()) {
                for(int i = 0; i < numWords; i++) {
                    s += words[start+i];
                    if(i < numWords-1) {
                        s.push_back(' ');
                    }
                }
                for(int i = 0; i < maxWidth-length; i++) {
                    s.push_back(' ');
                }
            }
            else {
                int extraSpaceNum = (maxWidth-length) / (numWords-1);
                int offset = (maxWidth - length) - extraSpaceNum * (numWords-1);
                for(int i = 0; i < offset; i++) {
                    s += words[start+i];
                    for(int j = 0; j <= extraSpaceNum; j++) {
                        s.push_back(' ');
                    }
                    s.push_back(' ');
                }
                for(int i = offset; i < numWords; i++) {
                    s += words[start+i];
                    if(i < numWords-1) {
                        for(int j = 0; j < extraSpaceNum; j++) {
                            s.push_back(' ');
                        }
                        s.push_back(' ');
                    }
                }
            }
            result.push_back(s);
        }
        return result;
    }
private:
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    Solution sol;
    vector<string> words{"This", "is", "an", "example", "of", "text", "justification."};
    int L = 16;
    vector<string> result = sol.fullJustify(words, L);
    for(int i = 0; i < result.size(); i++) {
        cout << result[i] << endl;
    }
    return 0;
}
