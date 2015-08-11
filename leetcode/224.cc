#include "leetc.h"
#include <cctype>
#include <stack>

using std::stack;

class Solution {
public:
    int calculate(string s) {
        stack<int> nums;
        stack<int> opts;
        int i = 0;
        skip(s, i);
        while(i < s.size()) {
            if(std::isdigit(s[i])) {
                nums.push(nextInteger(s, i));
            }
            else {
                int opt = s[i];
                if(opt == '(') opts.push(opt);
                else if(opt == ')') {
                    while(opts.top() != '(') {
                        int opt2 = opts.top(); opts.pop();
                        int rhs = nums.top(); nums.pop();
                        int lhs = nums.top(); nums.pop();
                        nums.push(compute(lhs, rhs, opt2));
                    }
                    opts.pop();
                }
                else {
                    if(opts.empty() || opts.top() == '(') opts.push(opt);
                    else {
                        int opt2 = opts.top(); opts.pop();
                        int rhs = nums.top(); nums.pop();
                        int lhs = nums.top(); nums.pop();
                        nums.push(compute(lhs, rhs, opt2));
                        opts.push(opt);
                    }
                }
                i++;
            }
            skip(s, i);
        }
        if(!opts.empty()) {
            int opt = opts.top(); opts.pop();
            int rhs = nums.top(); nums.pop();
            int lhs = nums.top(); nums.pop();
            nums.push(compute(lhs, rhs, opt));
        }
        return nums.top();
    }

    int nextInteger(string &s, int &i) {
        int result = s[i++]-'0';
        while(i < s.size() && std::isdigit(s[i])) {
            result = result*10 + (s[i++]-'0');
        }
        return result;
    }

    inline void skip(string &s, int &i) {
        while(i < s.size() && std::isblank(s[i])) i++;
    }
    
    inline int compute(int lhs, int rhs, int op) {
        if(op == '+')
            return lhs+rhs;
        else 
            return lhs-rhs;
    }
};

Solution sol;

int main(void) {
    string s;
    cin >> s;
    cout << sol.calculate(s) << endl;
    return 0;
}
