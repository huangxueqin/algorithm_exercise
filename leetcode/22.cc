#include "leetc.h"

using namespace std;

class Solution {
    public:
        vector<string> generateParenthesis(int n) {
            vector<string> result;
            solution(result, n);
            return result;
        }
    private:
        void solution(vector<string> &result, int n) {
            if(n > 0) {
                string parenthesis = "";
                create_parenthesis(result, parenthesis, 0, 0, n);
            }
        }
        void create_parenthesis(vector<string> &result, string &parenthesis,
                const int pleft, const int pright, const int n) {
            if(pleft == n && pright == n)
                result.push_back(parenthesis);
            else {
                if(pright < pleft) {
                    parenthesis.push_back(')');
                    create_parenthesis(result, parenthesis, pleft, pright+1, n);
                    parenthesis.pop_back();
                }
                if(pleft < n) {
                    parenthesis.push_back('(');
                    create_parenthesis(result, parenthesis, pleft+1, pright, n);
                    parenthesis.pop_back();
                }
            }
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    if(argc < 2) printf("need parameter\n");
    int n = std::atoi(argv[1]);
    vector<string> result = sol.generateParenthesis(n);
    print_vector(result);
    return 0;
}
