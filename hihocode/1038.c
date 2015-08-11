#include "hihocode.h"


#define MAX(a, b) ((a) < (b) ? (b) : (a))

long long _cal(size_t *need, size_t *value, size_t n, 
        long long *dp1, long long *dp2, size_t m) {
    for(int i=1;i<n;i++) {
        for(int k=0;k<=m;k++) {
            if(k < need[i])
                dp2[k] = dp1[k];
            else {
                dp2[k] = MAX(value[i] + dp1[k-need[i]], dp1[k]);
            }
        }
        memcpy(dp1, dp2, sizeof(long long) * (m+1));
    }
    return dp1[m];
}

int main(void) {
    size_t n, m;
    scanf("%zu %zu", &n, &m);
    size_t *need = (size_t *)malloc(sizeof(size_t) * n);
    size_t *value = (size_t *)malloc(sizeof(size_t) * n);
    for(int i=0;i<n;i++) {
        scanf("%zu %zu", need+i, value+i);
    }
    long long *dp1 = (long long *)malloc(sizeof(long long) * (m+1));
    long long *dp2 = (long long *)malloc(sizeof(long long) * (m+1));
    for(int i=0;i<=m;i++) {
        if(i < need[0])
            dp1[i] = 0;
        else
            dp1[i] = value[0];
    }
    memset(dp2, 0, sizeof(long long) * m);
    long long result = _cal(need, value, n, dp1, dp2, m);
    printf("%lld\n", result); 
    free(value);
    free(need);
    free(dp1);
    free(dp2);
    return 0;
}
