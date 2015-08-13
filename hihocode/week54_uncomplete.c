#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 20000
#define MAXM 200000
#define min(a, b) ((a) <= (b) ? (a) : (b))
#define max(a, b) ((a) >= (b) ? (a) : (b)) 

struct ge {
    int v;
    struct ge *next;
};

struct ge *new_ge(int v, struct ge *next) {
    struct ge *ge = (struct ge *) malloc(sizeof(struct ge));
    ge->v = v;
    ge->next = next;
    return ge;
}

void free_graph(struct ge *graph[], int n) {
    int i;
    for(i = 0; i < n; i++) {
        struct ge *p = graph[i];
        while(p) {
            struct ge *tmp = p;
            p = p->next;
            free(tmp);
        }
    }
}

int N, M;
int from[MAXM];
int to[MAXM];
struct ge *graph[MAXN];

int parent[MAXN];

int lowlink[MAXN];
int indices[MAXN];
int idx = 0;

int stack[MAXN];
int top = 0;

int grp_pst[MAXN];
int group[MAXN];
int gnum = 0;

void tarjan(int s) {
    indices[s] = idx;
    lowlink[s] = idx;
    idx += 1;
    stack[top++] = s;

    int child_cnt = 0;
    struct ge *p = graph[s];
    while(p) {
        int v = p->v;
        if(indices[v] == -1) {
            child_cnt += 1;
            parent[v] = s;
            tarjan(v);
            lowlink[s] = min(lowlink[s], lowlink[v]);

            if((parent[s] == -1 && child_cnt > 1) || (parent[s] != -1 && lowlink[v] >= indices[s])) {
                while(stack[top-1] != s) {
                    group[stack[top-1]] = gnum;
                    top--;
                }
                top--;
                gnum += 1;
            }

        }
        else if(parent[v] != s) {
            lowlink[s] = min(lowlink[s], indices[v]);
        }
        p = p->next;
    }
}

int main(void) {
    int i, u, v;
    scanf("%d %d", &N, &M);
    for(i = 0; i < M; i++) {
        scanf("%d %d", &u, &v);
        u--, v--;
        from[i] = u;
        to[i] = v;
        graph[u] = new_ge(v, graph[u]);
        graph[v] = new_ge(u, graph[v]);
    }

    memset(indices, -1, sizeof indices);
    memset(parent, -1, sizeof parent);
    memset(group, -1, sizeof group);

    for(i = 0; i < N; i++) {
        if(indices[i] == -1) {
            tarjan(i);
            if(top > 0) {
                while(top > 0) {
                    group[stack[top-1]] = gnum;
                    top--;
                }
                gnum++;
            }
        }
    }

    /* for(int i = 0; i < N; i++) {
     *     printf("%d ", group[i]);
     * }
     * printf("\n"); */
    memset(grp_pst, 0, sizeof grp_pst);
    printf("%d\n", gnum);
    for(i = 0; i < M; i++) {
        int g = group[from[i]] != -1 ? group[from[i]] : group[to[i]];
        if(g == -1) {
            printf("%d", i+1);
        }
        else {
            if(!grp_pst[g]) {
                grp_pst[g] = i+1;
            }
            printf("%d", grp_pst[g]);
        }

        if(i < M-1) printf(" ");
        else printf("\n");
    }

    free_graph(graph, N);
    return 0;
}
