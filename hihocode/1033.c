#include "hihocode.h"

#define nMax 20
#define kMax 300
#define MOD 1000000007
#define PRE(bit, k) (200 + bit - k)

typedef struct Info {
    long long sum;
    long long num;
} Info;

Info dp[nMax][kMax];
int bits[nMax];
long long rank[nMax];
int yy;

Info dfs(int pos, int s, bool limit) {
    /* printf("%d, %d\n", pos, s); */
    Info info;
    info.num = 0;
    info.sum = 0;
    if(pos == -1) {
        if(s == 100) info.num = 1;
        return info;
    }
    if(!limit && ~dp[pos][s].num)
        return dp[pos][s];

    int head = pos==yy ? 1 : 0;
    int i;
    int end = limit ? bits[pos] : 9;
    long long sum = 0l, num = 0l;
    for(i=head;i<=end;i++) {
        info = dfs(pos-1, PRE(i, s), limit && i == end);
        if(info.num > 0) {
            sum += ((rank[pos] * i) * (info.num%MOD))%MOD + info.sum;
            sum %= MOD;
            num += info.num;
        }
    }
    info.sum = sum;
    info.num = num;
    if(!limit) {
        dp[pos][s] = info;
    }
    return info;
}

long long cal(long long x, int k) {
    k += 100;
    int i = 0;
    while(x > 0) {
        bits[i] = x % 10;
        x /= 10;
        i++;
    }
    i--;
    long long sum = 0l;
    for(yy=0;yy<=i;yy++) {
        memset(dp, -1, sizeof(dp));
        sum += dfs(yy, k, yy==i).sum;
        sum %= MOD;
    }
    return sum;
}

int main(int argc, char *argv[]) {
    memset(dp, -1, sizeof(dp));
    rank[0] = 1l;
    int i=1;
    for(;i<nMax;i++)
        rank[i] = (rank[i-1] * 10) % MOD;
    long long l, r;
    int k;
    scanf("%lld %lld %d", &l, & r, &k);
    printf("%lld\n", cal(r, k) - cal(l-1, k));
    return 0;
}
