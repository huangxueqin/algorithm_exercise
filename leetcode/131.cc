/*
 * Manacher's Algorithm Dec/25/14
 */

#include "leetc.h"
#include <vector>
#include <stack>

using namespace std;

class Solution {
    public:
        vector<vector<string>> partition(string s) {
            vector<vector<string>> result;
            vector<string> svec;
            vector<vector<int>> table(s.size(), vector<int>(s.size(), -1));
            make_partition(result, svec, table, s, 0);
            return result;
        }
    private:
        void make_partition(vector<vector<string>> &result, vector<string> &svec, 
                vector<vector<int>> &table, const string &s, size_t start) {
            if(start < s.size()) {
                size_t pos = start;
                while(pos < s.size()) {
                    if(is_parlindrome(table, s, start, pos)) {
                        svec.push_back(s.substr(start, pos-start+1));
                        make_partition(result, svec, table, s, pos+1);
                        svec.pop_back();
                    }
                    pos++;
                }
            }
            else {
                result.push_back(svec);
            }
        }

        int is_parlindrome(vector<vector<int>> &table, const string &s, int i, int j) {
            if(i < j) {
                if(table[i][j] == -1) {
                    if(s[i] == s[j] && is_parlindrome(table, s, i+1,j-1) == 1)
                        table[i][j] = 1;
                    else
                        table[i][j] = 0;
                }
                return table[i][j];
            }
            return  1;
        }
};

template <typename T>
void print_table(vector<vector<T>> &table) {
    typename vector<vector<T>>::iterator iter1 = table.begin();
    while(iter1 != table.end()) {
        typename vector<T>::iterator iter2 = iter1->begin();
        while(iter2 != iter1->end()) {
            cout << *iter2 << " ";
            iter2++;
        }
        cout << endl;
        iter1++;
    }
}
int main() {
    string s = "ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc";
    Solution sol;
    vector<vector<string>> svv = sol.partition(s);
    print_table(svv);
    return 0;
}
