#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50010
#define RT 1
#define LC(r) ((r) << 1)
#define RC(r) (((r) << 1) | 1)
#define OFFSET(head, N, x) (((x) > (head)) ? ((x)-(head)) : ((x)+(N)-(head)))

struct segment_node {
    int l, r;
    int same;
    int add;
    int delta, inc;
} tree[MAXN*4];

void build_tree(int rt, int l, int r);
void update_by_cmd1(int rt, int l, int r, char X);
void update_by_cmd2(int rt, int l, int r, int K);
void update_by_cmd4(int rt, int l, int r);
void obtain_string(int rt, char *out);


char str[MAXN] = {0};
char cmd_head[4];
int cmd_num;
int head = 0;

int main(void) {
    int N, M, i, j, K;
    char X;
    scanf("%d %d", &N, &M);
    for(int k = 0; k < N; k++) 
        scanf("%c", str+k+1);
    build_tree(1, 1, N);
    for(int m = 0; m < M; m++) {
        scanf("%s %d", cmd_head, &cmd_num);
        switch(cmd_num) {
            case 1:
                scanf("%d %d %c", &i, &j, &X);
                i = OFFSET(head, N, i);
                j = OFFSET(head, N, j);
                update_by_cmd1(RT, i, j, X);
                break;
            case 2:
                break;
                scanf("%d %d %d", &i, &j, &K);
                i = OFFSET(head, N, i);
                j = OFFSET(head, N, j);
                update_by_cmd2(RT, i, j, K);
            case 3:
                scanf("%d", &K);
                head = (head + K) % N;
                break;
            case 4:
                scanf("%d %d", &i, &j);
                i = OFFSET(head, N, i);
                j = OFFSET(head, N, j);
                update_by_cmd4(RT, i, j);
                break;
        }
    }
    obtain_string(RT, str);

    // print result
    for(int i = head + 1; i <= N; i++) {
        printf("%c", str[i]);
    }
    for(int i = 1; i <= head; i++) {
        printf("%c", str[i]);
    }
    printf("\n");

    return 0;
}

void obtain_string(int rt, char *out) {
    if(tree[rt].l == tree[rt].r) {
        out[tree[rt].l] = (tree[rt].same + tree[rt].add + tree[rt].delta) % 26 + 'A';
    }
    else {
        obtain_string(LC(rt), out);
        obtain_string(RC(rt), out);
    }
}

void build_tree(int rt, int l, int r) {
    tree[rt].l = l;
    tree[rt].r = r;
    tree[rt].add = tree[rt].delta = tree[rt].inc = 0;
    if(l == r) {
        tree[rt].same = str[rt] - 'A';
    }
    else {
        int m = (l+r) >> 1;
        build_tree(LC(rt), l, m);
        build_tree(RC(rt), m+1, r);
        tree[rt].same = (tree[LC(rt)].same != -1 && tree[LC(rt)].same == tree[RC(rt)].same) ? 
            -1 : tree[LC(rt)].same;
    }
}

void update_by_cmd1(int rt, int l, int r, char X) {
    if(tree[rt].r < l || tree[rt].l > r) return;
    if(tree[rt].l >= l && tree[rt].r <= r) {
        tree[rt].same = X - 'A';
    }
    if(tree[rt].l < tree[rt].r) {
        update_by_cmd1(LC(rt), l, r, X);
        update_by_cmd1(RC(rt), l, r, X);
    }
}

void update_by_cmd2(int rt, int l, int r, int K) {
    if(tree[rt].r < l || tree[rt].l > r) return;
    if(tree[rt].l >= l && tree[rt].r <= r) {
        tree[rt].add += K;
    }
    if(tree[rt].l < tree[rt].r) {
        update_by_cmd2(LC(rt), l, r, K);
        update_by_cmd2(RC(rt), l, r, K);
    }
}

void update_by_cmd4(int rt, int l, int r) {
    if(tree[rt].r < l || tree[rt].l > r) return;
    if(tree[rt].l >= l && tree[rt].r <= r) {
        int delta_delta = 1 + l - tree[rt].l;
        tree[rt].delta += delta_delta;
        tree[rt].inc += 1;
    }
    else {
        tree[rt].same = -1;
    }
    if(tree[rt].l < tree[rt].r) {
        update_by_cmd4(LC(rt), l, r);
        update_by_cmd4(RC(rt), l, r);
    }
}
