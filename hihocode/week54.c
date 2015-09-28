#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 20001
#define MAXM 200001
#define min(a, b) ((a) <= (b) ? (a) : (b))
#define max(a, b) ((a) >= (b) ? (a) : (b)) 

struct edge {
    int v;
    struct edge *next;
};

struct graph {
    int nv;
    struct edge *adjs[MAXN];
};

int pool_avail = 0;
struct edge edge_pool[MAXM] = {{0, NULL}};
int pool_avail2 = 0;
struct edge edge_pool2[MAXM] = {{0, NULL}};

int nv, ne;
struct graph graph = {0, {NULL}};
int grass[MAXN] = {0};

int mark[MAXN][MAXN] = {{0}};
struct graph graph2 = {0, {NULL}};

int grp_num = 0;
int group[MAXN] = {0};
int grp_grs[MAXN] = {0};

int visit_num = 0;
int visit[MAXN];
int low_link[MAXN];
int stack[MAXN] = {0};
int on_stack[MAXN] = {0};
int sp = 0;

int max_grass = 0;

void tarjan(int s) {
    visit[s] = low_link[s] = visit_num++;
    stack[sp++] = s;
    on_stack[s] = 1;

    struct edge *e = graph.adjs[s];
    while(e) {
        int v = e->v;
        if(visit[v] == -1) {
            tarjan(v);
            low_link[s] = min(low_link[s], low_link[v]);
        }
        else if(on_stack[v]) {
            low_link[s] = min(low_link[s], visit[v]);
        }
        e = e->next;
    }
    if(low_link[s] == visit[s]) {
        int total_grass = 0;
        while(sp > 0 && stack[sp-1] != s) {
            group[stack[sp-1]] = grp_num;
            on_stack[stack[sp-1]] = 0;
            total_grass += grass[stack[sp-1]];
            sp--;
        }
        sp--;
        group[s] = grp_num;
        on_stack[s] = 0;
        total_grass += grass[s];
        grp_grs[grp_num] = total_grass;
        grp_num++;
    }
}

void construct_grouped_graph() {
    graph2.nv = grp_num;
    int u;
    for(u = 0; u < nv; u++) {
        struct edge *e = graph.adjs[u];
        while(e) {
            int v = e->v;
            e = e->next;
            if(mark[group[u]][group[v]]) continue;
            mark[group[u]][group[v]] = 1;
            struct edge *edge = &(edge_pool2[pool_avail2++]);
            edge->v = group[v];
            edge->next = graph2.adjs[group[u]];
            graph2.adjs[group[u]] = edge;
        }
    }
}

void dfs(int s, int total_grass) {
    visit[s] = 1;
    total_grass += grp_grs[s];
    bool more = false;
    struct edge *e = graph2.adjs[s];
    while(e) {
        if(!visit[e->v]) {
            more = true;
            dfs(e->v, total_grass);
        }
        e = e->next;
    }

    if(!more) {
        max_grass = max(max_grass, total_grass);
    }
}

int main(void) {
    scanf("%d %d\n", &nv, &ne);
    int i, u, v;
    for(i = 0; i < nv; i++) 
        scanf("%d", grass+i);
    for(i = 0; i < ne; i++) {
        scanf("%d %d", &u, &v);
        u--; v--;
        struct edge *edge = &(edge_pool[pool_avail++]);
        edge->v = v;
        edge->next = graph.adjs[u];
        graph.adjs[u] = edge;
    }

    memset(visit, -1, sizeof visit);
    memset(low_link, -1, sizeof low_link);
    tarjan(0);

    /* for(i = 0; i < nv; i++) {
     *     printf("%d: %d\n", i, group[i]);
     * }
     * for(i = 0; i < grp_num; i++) {
     *     printf("%d ", grp_grs[i]);
     * }
     * printf("\n"); */
    // printf("grp_num = %d\n", grp_num);

    construct_grouped_graph();
    
    memset(visit, 0, sizeof visit);
    dfs(group[0], 0);
    printf("%d\n", max_grass);
    return 0;
}
