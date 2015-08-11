#include "hihocode.h"

#define nMax 10

long long dp[nMax][100];
int num[nMax];
int n;

int cal_pre(int bit, int s) {
    while(s < bit) s += n;
    return s - bit;
}

long long dfs(int pos, int s, bool limit) {
    if(pos == -1) {
        if(!s) return 1;
        else return 0;
    }
    if(!limit && ~dp[pos][s])
        return dp[pos][s];

    int head = 0, tail = limit ? num[pos] : 9;
    long long sum = 0l;
    int i;
    for(i=head;i<=tail;i++) {
        sum += dfs(pos-1, cal_pre(i, s), limit && i==tail);
    }
    if(!limit)
        dp[pos][s] = sum;
    return sum;
}

long long cal(long long x) {
    int i = 0;
    while(x > 0) {
        num[i++] = x % 10;
        x /= 10;
    }
    i--;
    return dfs(i, 0, true);
}

int main(int argc, char *argv[]) {
    memset(dp, -1, sizeof(dp));
    long long l, r;
    int mod;
    scanf("%lld %lld %d", &l, &r, &mod);
    n = mod;
    printf("%lld\n", cal(r) - cal(l-1));
    return 0;
}
