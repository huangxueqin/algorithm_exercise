include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50010
#define RT 1
#define LC(r) ((r) << 1)
#define RC(r) (((r) << 1) | 1)

#define OFFSET(head, N, x) (((head) + (x)) % (N))
#define INSIDE(l, r, N, ll, rr) (\
        (l) <= (r) ? \
        ((l) <= (ll) && (r) >= (rr)) : \
        (((l) <= (ll) && (N) >= (rr)) || (0 <= (ll) && (r) >= (rr))) \
        )
#define OUTSIDE(l, r, N, ll, rr) ( \
        (l) <= (r) ? \
        ((rr) < (l) || (ll) > (r)) : \
        ((ll) > (r) && (rr) < (l)) \
        )
#define LEFT_DIST(l, N, ll) (\
        (l) <= (ll) ? \
        ((ll) - (l)) : \
        ((N) - ((l) - (ll))) \
        )


struct segment_node {
    int l, r;
    int same;
    int add;
    int delta, inc;
} tree[MAXN*4];

void build_tree(int rt, int l, int r);
void update_by_cmd1(const int N, int rt, int l, int r, char X);
void update_by_cmd2(const int N, int rt, int l, int r, int K);
void update_by_cmd4(const int N, int rt, int l, int r);
void obtain_string(int rt, char *out);
void print_string(char *str, const int N, const int head);


char str[MAXN] = {0};
char cmd_head[4];
int cmd_num;
int head = 0;

int main(void) {
    int N, M, i, j, K;
    char X;
    scanf("%d %d\n", &N, &M);
    for(int k = 0; k < N; k++) {
        scanf("%c", str+k+1);
    }
    //printf("%s", str+1);
    // skip new line
    getchar();
    build_tree(1, 1, N);
    for(int m = 0; m < M; m++) {
        scanf("%s %d", cmd_head, &cmd_num);
        switch(cmd_num) {
            case 1:
                scanf("%d %d %c\n", &i, &j, &X);
                i = OFFSET(head, N, i);
                j = OFFSET(head, N, j);
                update_by_cmd1(N, RT, i, j, X);
                //printf("after cmd1: ");
                //print_string(str, N, head);
                break;
            case 2:
                scanf("%d %d %d\n", &i, &j, &K);
                i = OFFSET(head, N, i);
                j = OFFSET(head, N, j);
                update_by_cmd2(N, RT, i, j, K);
                //printf("after cmd2: ");
                //print_string(str, N, head);
                break;
            case 3:
                scanf("%d\n", &K);
                head = (head + K) % N;
                //printf("after cmd3: ");
                //print_string(str, N, head);
                break;
            case 4:
                scanf("%d %d\n", &i, &j);
                i = OFFSET(head, N, i);
                j = OFFSET(head, N, j);
                update_by_cmd4(N, RT, i, j);
                //printf("%d %d: ", i, j);
                //printf("after cmd4: ");
                //print_string(str, N, head);
                break;
        }
        getchar();
    }
    print_string(str, N, head);

    return 0;
}

void print_string(char *str, const int N, const int head) {
    obtain_string(RT, str);
    // print result
    for(int i = head + 1; i <= N; i++) {
        printf("%c", str[i]);
    }
    for(int i = 1; i <= head; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
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
        tree[rt].same = str[l] - 'A';
        //printf("%d[%c]", l, str[l]);
    }
    else {
        int m = (l+r) >> 1;
        build_tree(LC(rt), l, m);
        build_tree(RC(rt), m+1, r);
        tree[rt].same = (tree[LC(rt)].same != -1 && tree[LC(rt)].same == tree[RC(rt)].same) ? 
            -1 : tree[LC(rt)].same;
    }
}

void update_by_cmd1(int N, int rt, int l, int r, char X) {
    int ll = tree[rt].l, rr = tree[rt].r;
    if(OUTSIDE(l, r, N, ll, rr)) return;
    if(INSIDE(l, r, N, ll, rr)) {
        tree[rt].same = X - 'A';
    }
    if(tree[rt].l < tree[rt].r) {
        update_by_cmd1(N, LC(rt), l, r, X);
        update_by_cmd1(N, RC(rt), l, r, X);
    }
}

void update_by_cmd2(const int N, int rt, int l, int r, int K) {
    int ll = tree[rt].l, rr = tree[rt].r;
    if(OUTSIDE(l, r, N, ll, rr)) return;
    if(INSIDE(l, r, N, ll, rr)) {
        tree[rt].add += K;
    }
    if(tree[rt].l < tree[rt].r) {
        update_by_cmd2(N, LC(rt), l, r, K);
        update_by_cmd2(N, RC(rt), l, r, K);
    }
}

void update_by_cmd4(const int N, int rt, int l, int r) {
    int ll = tree[rt].l, rr = tree[rt].r;
    if(OUTSIDE(l, r, N, ll, rr)) return;
    if(INSIDE(l, r, N, ll, rr)) {
        int delta_delta = 1 + LEFT_DIST(l, N, ll);
        tree[rt].delta += delta_delta;
        tree[rt].inc += 1;
    }
    else {
        tree[rt].same = -1;
    }
    if(tree[rt].l < tree[rt].r) {
        update_by_cmd4(N, LC(rt), l, r);
        update_by_cmd4(N, RC(rt), l, r);
    }
}
