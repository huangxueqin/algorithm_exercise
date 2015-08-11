#include "leetc.h"

class Solution {
public:
    int trap(const int a[], const int n) {
        return trap(a, 0, n-1);
    }
private:
    int trap(const int a[], const int i, const int j) {
        if(j-i < 2) return 0;
        int maxh = -1, maxhi;
        int minorh = -1, minorhi;
        for(int k = i; k <= j; k++) {
            if(a[k] > maxh) {
                minorh = maxh;
                minorhi = maxhi;
                maxh = a[k];
                maxhi = k;
            }
            else if(a[k] > minorh) {
                minorh = a[k];
                minorhi = k;
            }
        }
        int j1 = std::min(maxhi, minorhi);
        int j2 = std::max(maxhi, minorhi);
        int cap = minorh * (j2 - j1 - 1);
        for(int k = j1 + 1; k < j2; k++) cap -= a[k];
        printf("j1, j2, cap = (%d, %d, %d)\n", j1, j2, cap);
        return cap + trap(a, i, j1) + trap(a, j2, j);
    }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int a[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    int result = sol.trap(a, sizeof(a) / sizeof(int));
    cout << "result = " << result << endl;
    return 0;
}
