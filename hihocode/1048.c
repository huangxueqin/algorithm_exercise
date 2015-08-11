#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;
const int MOD = 1000000007;
ll dp[1010][40];
int tran[40][40];
int mask[6] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20};
int N, M;

void init_tran_table_row(const int s, const int i, const int next, int * const pindex) {
    if(i >= M) {
        tran[s][*pindex] = next;
        (*pindex)++;
        return;
    }
    if((s&mask[i]) > 0) {
        init_tran_table_row(s, i+1, next, pindex);
    }
    else {
        init_tran_table_row(s, i+1, next|mask[i], pindex);
        if(i+1 < M && (s&mask[i+1]) == 0) {
            init_tran_table_row(s, i+2, next, pindex);
        }
    }
}

void init_tran_table() {
    int s;
    for(s = 0; s < (1<<M); s++) {
        int index = 0;
        init_tran_table_row(s, 0, 0, &index);
    }
    /* for(s = 0; s < (1<<M); s++) {
     *     int i = 0;
     *     printf("%d-> ", s);
     *     while(tran[s][i] != -1) {
     *         printf("%d ", tran[s][i]);
     *         i++;
     *     }
     *     printf("\n");
     * } */
}

ll run(const int n, const int s) {
    if(n == N)
        return s == 0 ? 1 : 0;
    if(dp[n][s] == -1) {
        dp[n][s] = 0;
        int i = 0;
        while(tran[s][i] != -1) {
            dp[n][s] += run(n+1, tran[s][i]);
            if(dp[n][s] > MOD) dp[n][s] -= MOD;
            i++;
        }
    }
    return dp[n][s];
}

int main(void) {
    ll result = 0;
    scanf("%d %d", &N, &M);
    if(((M * N) & 0x1) == 0) {
        memset(dp, -1, sizeof(dp));
        memset(tran, -1, sizeof(tran));
    }
    init_tran_table();
    result = run(0, 0);
    printf("%lld\n", result % MOD);
    return 0;
}
