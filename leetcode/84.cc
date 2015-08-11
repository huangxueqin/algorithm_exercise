#include "leetc.h"
#include <stack>

using std::stack;

class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
        stack<int> istack;
        int ma = 0;
        int n = height.size();
        for(int i = 0; i < n; i++) {
            int h = height[i];
            if(istack.empty() || h > height[istack.top()]) {
                istack.push(i);
            }
            else if(h == height[istack.top()]) {
                istack.pop();
                istack.push(i);
            }
            else {
                while(!istack.empty() && height[istack.top()] >= h) {
                    int iph = istack.top(); istack.pop();
                    if(height[iph] == h) continue;
                    int ipph = istack.empty() ? -1 : istack.top();
                    int a = height[iph] * (i - ipph-1);
                    if(ma < a) ma = a;
                }
                istack.push(i);
            }
        }

        while(!istack.empty()) {
            int ih = istack.top(); istack.pop();
            int iph = istack.empty() ? -1 : istack.top();
            int a = height[ih] * (n - iph -1);
            if(ma < a) ma = a;
        }

        return ma;
    }
};
