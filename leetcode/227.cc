#include "leetc.h"
#include <stack>

using std::stack;

class Solution {
public:
    int calculate(string s) {
        stack<char> ops;
        stack<int> nums;
        int i = 0;
        while(i < s.size()) {
            while(i < s.size() && std::isblank(s[i])) i++;
            if(i < s.size()) {
                nums.push(nextInteger(s, i));
            }
            while(i < s.size() && std::isblank(s[i])) i++;
            if(i < s.size()) {
                char op = nextOpt(s, i);
                if(!ops.empty()) {
                    char opt = ops.top();
                    while(!ops.empty() && !((op == '*' || op == '/')&&(opt == '+' || opt == '-'))) {
                        ops.pop();
                        int rhs = nums.top(); nums.pop();
                        int lhs = nums.top(); nums.pop();
                        int res = cal(lhs, rhs, opt);
                        nums.push(res);
                        if(!ops.empty()) 
                            opt = ops.top();
                    }
                }
                ops.push(op);
            }
        }
        while(!ops.empty()) {
            int rhs = nums.top(); nums.pop();
            int lhs = nums.top(); nums.pop();
            int op = ops.top(); ops.pop();
            int res = cal(lhs, rhs, op);
            nums.push(res);
        }
        return nums.top();
    }
private:

    // oprator precedence parsing, recursive
    int calculate(const string &s, int lhs, int i) {
        while(std::isblank(s[i])) i++;
        if(i >= s.size()) return lhs;
        int op = nextOpt(s, i);
        int rhs = nextInteger(s, i);
        if(op == '*' || op == '/') {
            lhs = cal(lhs, rhs, op);
            return calculate(s, lhs, i);
        }
        else {
            int op2 = nextOpt(s, i);
            if(op2 == '*' || op2 == '/') {
                return cal(lhs, calculate(s, rhs, i-1), op);
            }
            else {
                lhs = cal(lhs, rhs, op);
                return calculate(s, lhs, i-1);
            }
        }
    }

    inline int cal(int lhs, int rhs, int op) {
        switch(op) {
            case '+':
                return lhs + rhs;
            case '-':
                return lhs - rhs;
            case '*':
                return lhs * rhs;
            case '/':
                return lhs / rhs;
        }
        return 0;
    }

    int nextInteger(const string &s, int &i) {
        while(std::isblank(s[i])) i++;
        int r = 0;
        while(s[i] <= '9' && s[i] >= '0') {
            r = r*10 + s[i]-'0';
            i++;
        }
        return r;
    }
    
    char nextOpt(const string &s, int &i) {
        while(std::isblank(s[i])) i++;
        return s[i++];
    }
};

Solution sol;

int main(void) {
    string expr;
    while(true) {
        cin >> expr;
        cout << sol.calculate(expr) << endl;
    }
    return 0;
}
