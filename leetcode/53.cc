#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        int maxSubArray(int a[], int n) {
            return bf_max_subarray(a, n);
        }
    private:
        int bf_max_subarray(int a[], int n) {
            int s = 0, t = 0;
            int maxs = a[0];
            int sum = 0;
            while(t < n) {
                sum += a[t];
                ++t;
                if(sum > maxs)
                    maxs = sum;
                while(s < t && sum < 0) {
                    sum -= a[s];
                    ++s;
                }
            }
            return maxs;
        }
};

Solution sol;

template <typename T, size_t N>
constexpr size_t size_of(T (&)[N]) { return N; }
int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int a[] = {-2,1,-3,4,-1,2,1,-5,4};
    printf("max = %d\n", sol.maxSubArray(a, size_of(a)));
    return 0;
}
