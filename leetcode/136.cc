#include "leetc.h"

using namespace std;

class Solution {
    public:
        int singleNumber(int a[], int n) {
            int elmt = 0;
            for(int i = 0; i < n; i++) {
                elmt ^= a[i];
            }
            return elmt;
        }
};

int main(void) {
    int n;
    scanf("%d", &n);
    int *a = new int[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", a+i);
    }
    Solution s;
    printf("%d\n", s.singleNumber(a, n));
    delete a;
    return 0;
}
