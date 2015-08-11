#include "leetc.h"

using std::vector;
using std::string;

class Solution {
    public:
        int numDecodings(string s) {
            size_t n = s.size();
            if(n == 0) return 0;
            vector<int> dp(n, 0);
            for(size_t i = 0; i < n; i++) {
                if(i > 0) {
                    if(valid(s, i, i))
                        dp[i] += dp[i-1]; 
                    if(valid(s, i-1, i)) {
                        if(i > 1) dp[i] += dp[i-2];
                        else dp[i] += 1;
                    }
                }
                else {
                    dp[i] = valid(s, 0, 0) ? 1 : 0;
                }
            }
            return dp[n-1];
        }
    private:
        inline bool valid(const string &s, const size_t sp, const size_t ep) const{
            return (ep == sp && s[sp] >= '1' && s[sp] <= '9') ||
                ((sp + 1 == ep) && 
                 (s[sp] == '1' || (s[sp] == '2' && s[ep] <= '6'))
                 );
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    string s;
    if(argc == 1)
        s = "12";
    else 
        s = string(argv[1]);
    int num = sol.numDecodings(s);
    printf("%d\n", num);
    return 0;
}
