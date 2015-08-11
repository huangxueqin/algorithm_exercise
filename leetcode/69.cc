#include "leetc.h"
#include <climits>

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        int sqrt(int x) {
            if(x == 0) return 0;
            int i = 1;
            int r = x;
            while(i*i < x) {
                int mid = (r+i) < r ? r/2 : (r+i)/2;
                if(mid == i) break;
                int square = mid*mid;
                if(square/mid != mid) r = mid;
                else {
                    if(square > x) r = mid;
                    else if(square < x) i = mid;
                    else return mid;
                }
            }
            return i;
        }
    private:
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int x = 2147483647;
    printf("%d\n", sol.sqrt(x));
    return 0;
}
