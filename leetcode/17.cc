#include "leetc.h"

using namespace std;

class Solution {
    public:
        Solution() {
            vector<string> v0; v0.push_back(" ");
            vector<string> v1; v1.push_back("");
            vector<string> v2; v2.push_back("a"); v2.push_back("b"); v2.push_back("c");
            vector<string> v3; v3.push_back("d"); v3.push_back("e"); v3.push_back("f");
            vector<string> v4; v4.push_back("g"); v4.push_back("h"); v4.push_back("i");
            vector<string> v5; v5.push_back("j"); v5.push_back("k"); v5.push_back("l");
            vector<string> v6; v6.push_back("m"); v6.push_back("n"); v6.push_back("o");
            vector<string> v7; v7.push_back("p"); v7.push_back("q"); v7.push_back("r"); v7.push_back("s");
            vector<string> v8; v8.push_back("t"); v8.push_back("u"); v8.push_back("v");
            vector<string> v9; v9.push_back("w"); v9.push_back("x"); v9.push_back("y"); v9.push_back("z");
            table.push_back(v0);
            table.push_back(v1);
            table.push_back(v2);
            table.push_back(v3);
            table.push_back(v4);
            table.push_back(v5);
            table.push_back(v6);
            table.push_back(v7);
            table.push_back(v8);
            table.push_back(v9);
        }
        vector<string> letterCombinations(string digits) {
            vector<string> result;
            vector<string> svec;
            letter_combinations(result, svec, digits, 0);
            return result;
        }
    private:
        vector<vector<string>> table;

        void letter_combinations(vector<string> &result, vector<string> &svec, string &digits, int start) {
            if(start >= digits.size()) {
                result.push_back(vec_to_string(svec));
                return;
            }
            int index = digits[start]-'0';
            for(auto iter = table[index].begin();iter != table[index].end(); iter++) {
                svec.push_back(*iter);
                letter_combinations(result, svec, digits, start+1);
                svec.pop_back();
            }
        }
        
        string vec_to_string(vector<string> &svec) {
            string result="";
            for(auto iter=svec.begin();iter!=svec.end();iter++) {
                result += *iter;
            }
            return result;
        }
};

int main(void) {
    string digits = "23";
    Solution s;
    vector<string> svecs = s.letterCombinations(digits);
    print_vector(svecs);
    return 0;
}
