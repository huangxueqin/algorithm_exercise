#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 20000
#define MAXM 100000
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

int N, M;
struct ge *graph[MAXN];
int grass[MAXN];
int indices[MAXN];
int lowlink[MAXN];
int stack[MAXN];
bool onstack[MAXN];
int top = 0;
int idx = 0;
int groups[MAXN];
struct ge *graph2[MAXN];
int grass2[MAXN];
int group = 0;
bool bs[MAXN];

void tarjan(int s) {
    indices[s] = idx;
    lowlink[s] = idx;
    idx += 1;
    stack[top++] = s;
    onstack[s] = true;
    struct ge *p = graph[s];
    while(p) {
        int v = p->v;
        if(indices[v] == -1) {
            tarjan(v);
            lowlink[s] = min(lowlink[v], lowlink[s]);
        }
        else if(onstack[v]) {
            lowlink[s] = min(indices[v], lowlink[s]);
        }
        p = p->next;
    }

    if(lowlink[s] == indices[s]) {
        int i;
        for(i = 0; i < group; i++) bs[i] = false;
        grass2[group] = 0;
        graph2[group] = NULL;

        while(top > 0 && lowlink[stack[top-1]] >= indices[s]) {
            int u = stack[top-1];
            onstack[u] = false;
            groups[u] = group;
            grass2[group] += grass[u];
            struct ge *p = graph[u];
            while(p) {
                int v = p->v;
                if(groups[v] < groups[u] && !bs[groups[v]]) {
                    graph2[group] = new_ge(groups[v], graph2[group]);
                    bs[groups[v]] = true;
                }
                p = p->next;
            }
            top--;
        }
        group += 1;
    }
}

int max_grass[MAXN] = {0};
int compute_max_grass(int u) {
    if(!max_grass[u]) {
        int sum = 0;
        struct ge *p = graph2[u];
        while(p) {
            int v = p->v;
            sum = max(sum, compute_max_grass(v));
            p = p->next;
        }
        max_grass[u] = grass2[u] + sum;
    }
    return max_grass[u];
}

int main(void) {
    int i, u, v;
    scanf("%d %d", &N, &M);
    for(i = 0; i < N; i++) {
        scanf("%d", grass+i);
    }
    for(i = 0; i < M; i++) {
        scanf("%d %d", &u, &v);
        u--, v--;
        graph[u] = new_ge(v, graph[u]);
    }
    memset(indices, -1, sizeof(indices));
    tarjan(0);
/*     for(int i = 0; i < N; i++) {
 *         printf("%d %d, ", i, groups[i]);
 *     }
 *     printf("\n");
 * 
 *     for(int i = 0; i < group; i++) {
 *         printf("%d\n", compute_max_grass(i));
 *     } */
    printf("%d\n", compute_max_grass(groups[0])); 

    for(i = 0; i < N; i++) {
        struct ge *p = graph[i];
        while(p) {
            struct ge *tmp = p;
            p = p->next;
            free(tmp);
        }
    }
    for(i = 0; i < group; i++) {
        struct ge *p = graph2[i];
        while(p) {
            struct ge *tmp = p;
            p = p->next;
            free(tmp);
        }
    }
    return 0;
}
