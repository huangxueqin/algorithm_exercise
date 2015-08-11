#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

int N, M, Q;
int W[1010];
int dp[1025][1010];
int mask;
int mask2;

int run(const int state, const int q, const int n) {
    if(n >= N) 
        return 0;
    if(dp[state][n] == -1) {
        int t = (state & mask) > 0 ? 1 : 0;
        int s1 = run((state << 1) & mask2, q-t, n+1);
        int s2 = (q-t < Q) ? (run(((state << 1) | 1) & mask2, q-t+1, n+1) + W[n]) : 0;
        dp[state][n] = max(s1, s2);
    }
    return dp[state][n];
}

int main(void) {
    int i;
    scanf("%d %d %d", &N, &M, &Q);
    for(i = 0; i < N; i++) 
        scanf("%d", W+i);
    mask = 1 << (M-1);
    mask2 = (1 << M) - 1;
    memset(dp, -1, sizeof(dp));
    printf("%d\n", run(0, 0, 0));
    return 0;
}
