#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    private:
    public:
        void sortColors(int a[], int n) {
            int i = 0, j = n - 1;
            const int ibits[] = {0b1, 0b10, 0b100};
            const int jbits[] = {0b1000, 0b10000, 0b100000};
            while(j > i) {
                /* printf("%d, %d--->%d, %d\n", i, j, a[i], a[j]); */
                int flag = ibits[a[i]] | jbits[a[j]];
                switch(flag) {
                    // 0, 2
                    case 0b100001:
                        i++; j--;
                        break;
                        // 2, 0
                    case 0b1100:
                        swap(a, i, j);
                        i++; j--;
                        break;
                        // 1, 0
                    case 0b1010:
                        swap(a, i, j);
                        i++;
                        break;
                        // 0, 1
                    case 0b10001:
                        i++;
                        break;
                        // 1, 2
                    case 0b100010:
                        j--;
                        break;
                        // 2, 1
                    case 0b10100:
                        swap(a, i, j);
                        j--;
                        break;
                        // 0, 0
                    case 0b1001:
                        while(i < n && a[i] == 0) i++;
                        if(i < n) {
                            swap(a, i, j);
                            i++;
                        }
                        break;
                        // 1, 1
                    case 0b10010:
                        {
                            int k = i;
                            int s = j;
                            while(k < j && a[k] < 2) k++;
                            if(k < j) {
                                swap(a, k, j);
                                j--;
                            }
                            while(s > i && a[s] > 0) s--;
                            if(s > i) {
                                swap(a, s, i);
                                i++;
                            }
                            if(k == j && s == i) return;
                        }
                        break;
                        // a[i] == 2, a[j] == 2
                    case 0b100100:
                        {
                            while(j >= 0 && a[j] == 2) j--;
                            if(j >= 0) {
                                swap(a, i, j);
                                j--;
                            }
                        }
                        break;
                }
            }
        }
    private:
        inline void swap(int a[], int i, int j) {
            int tmpi = a[i];
            a[i] = a[j];
            a[j] = tmpi;
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int a[] = {0,0,2,2,1,0,2,1,2,0,0,2,2,2};
    int len = sizeof(a) / sizeof(int);
    sol.sortColors(a, len);
    for(int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
