#include "leetc.h"
#include <climits>

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        int divide(int divident, int divisor) {
            if(divident == 0) return 0;
            if(divisor == 0 || 
                    (divident == INT_MIN && divisor == -1)) return INT_MAX;
            bool fneg = (divident > 0 && divisor < 0) || 
                (divident < 0 && divisor > 0);
            int64_t ldivident = divident > 0 ? divident : -(int64_t)divident;
            int64_t ldivisor = divisor > 0 ? divisor : -(int64_t)divisor;
            int result = 0;
            if(ldivident >= ldivisor) {
                int base = 1;
                int64_t rsldivisor = ldivisor;
                while(rsldivisor << 1 <= ldivident) {
                    rsldivisor <<= 1;
                    base <<= 1;
                }
                while(ldivident >= ldivisor) {
                    while(ldivident >= rsldivisor) {
                        result += base;
                        ldivident -= rsldivisor;
                    }
                    rsldivisor >>= 1;
                    base >>= 1;
                }
            }
            return fneg ? -(result) : result;
        }
    private:
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int divident = 2147483647;
    int divisor = 1;
    printf("%d\n", sol.divide(divident, divisor)); 
    return 0;
}
