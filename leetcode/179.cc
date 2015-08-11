#include "leetc.h"
#include <sstream>
#include <algorithm>

using namespace std;

class Solution {
    private:
        class CompoundElmt {
            public:
                int num;
                int bits[32];
                int bits_num;
                CompoundElmt(int x) : num(x){
                    int i = 0;
                    if(x == 0) {
                        bits[0] = 0;
                        bits_num = 1;
                        return;
                    }
                    while(x > 0) {
                        bits[i] = x % 10;
                        x /= 10;
                        i++;
                    }
                    bits_num = i;
                }
        };
        struct Compare {
            bool operator() (const Solution::CompoundElmt &lhs, const Solution::CompoundElmt &rhs) {
                const int len = lhs.bits_num + rhs.bits_num;
                for(int i=len-1;i>=0;i--) {
                    int a = i >= lhs.bits_num ? rhs.bits[i-lhs.bits_num] : lhs.bits[i];
                    int b = i >= rhs.bits_num ? lhs.bits[i-rhs.bits_num] : rhs.bits[i];
                    if(a > b) return true;
                    else if(a < b) return false;
                }
                return false;
            }
        } myComp;
    public:
        string largestNumber(vector<int> &num) {
            vector<Solution::CompoundElmt> num_bits;
            for(auto it = num.begin();it < num.end();it++) {
                Solution::CompoundElmt e(*it);
                num_bits.push_back(e);
            }
            std::sort(num_bits.begin(), num_bits.end(), myComp);
            stringstream ss;
            if(num_bits.back().num == 0)
                return "0";
            for(int i = num_bits.size(); i>0; i--) {
                ss << num_bits[i-1].num;
            }
            return ss.str();
        }
    private:
        static int get_bits(int x, int *bits) {
            int i = 0;
            while(x > 0) {
                bits[i] = x % 10;
                x /= 10;
                i++;
            }
            return i;
        }
};

int main(void) {
    int num[] = { 3, 30, 34, 5, 9 };
    vector<int> nvec(num, num+5);
    Solution s;
    cout << s.largestNumber(nvec) << endl;
    return 0;
}
