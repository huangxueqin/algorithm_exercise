#include "leetc.h"
#include <assert.h>
#include <stack>

using namespace std;

class Solution {
    public:
        int evalRPN(vector<string> &tokens) {
            stack<int> result;
            for(auto it = tokens.begin(); it != tokens.end(); it++) {
                if(!is_opt(*it)) {
                    result.push(std::stoi(*it));
                }
                else {
                    assert(result.size() >= 2);
                    int rhs = result.top(); result.pop();
                    int lhs = result.top(); result.pop();
                    result.push(compute(lhs, rhs, (*it).at(0)));
                }
            }
            assert(result.size() == 1);
            return result.top();
        }
    private:
        inline int compute(int lhs, int rhs, char op) {
            int result;
            switch(op) {
                case '+':
                    result = lhs + rhs; break;
                case '-':
                    result = lhs - rhs; break;
                case '*':
                    result = lhs * rhs; break;
                case '/':
                    result = lhs / rhs; break;
            }
            return result;
        }
        inline bool is_opt(string s) {
            if(s.size() != 1) return false;
            char op = s.at(0);
            return op == '+' ||
                op == '-' ||
                op == '*' ||
                op == '/';
        }
};

Solution sol;

int main(void) {
    string rpe1[] = {"2", "1", "+", "3", "*"};
    string rpe2[] = {"4", "13", "5", "/", "+"};
    vector<string> tokens1(rpe1, rpe1+5);
    vector<string> tokens2(rpe2, rpe2+5);
    cout << sol.evalRPN(tokens1) << endl;
    cout << sol.evalRPN(tokens2) << endl;
    return 0;
}
