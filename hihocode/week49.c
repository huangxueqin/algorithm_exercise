#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct disjoint_set {
    int num_roots;
    int *parent;
    int *elements;
} disjoint_set;

disjoint_set *create_disjoint_set(size_t n) {
    disjoint_set *dj_set = (disjoint_set *)malloc(sizeof(disjoint_set));
    dj_set->num_roots = n;
    dj_set->parent = (int *)malloc(sizeof(int) * n);
    dj_set->elements = (int *)malloc(sizeof(int) * n);
    int i = 0;
    for(; i < n; i++) {
        dj_set->parent[i] = i;
        dj_set->elements[i] = i;
    }
    return dj_set;
}

int parent(disjoint_set *dj_set, int x) {
    if(dj_set->parent[x] != x) {
        dj_set->parent[x] = parent(dj_set, dj_set->parent[x]);
    }
    return dj_set->parent[x];
}

void merge(disjoint_set *dj_set, int x, int y) {
    int px = parent(dj_set, x);
    int py = parent(dj_set, y);
    if(px != py) {
        dj_set->num_roots--;
        dj_set->parent[px] = py;
    }
}

void destroy(disjoint_set *dj_set) {
    free(dj_set->parent);
    free(dj_set->elements);
    free(dj_set);
}

int main(void) {
    int N, M;
    scanf("%d %d", &N, &M);
    int *degrees = (int *)malloc(sizeof(int) * N);
    memset(degrees, 0, sizeof(int) * N);
    disjoint_set *dj_set = create_disjoint_set(N);
    int i = 0;
    for(; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        degrees[u]++;
        degrees[v]++;
        merge(dj_set, u, v);
    }
    if(dj_set->num_roots > 1) {
        printf("Part\n");
    }
    else {
        int num_odd_degree_v = 0;
        int k = 0;
        for(; k < N; k++) {
            if(degrees[k] & 0x1) 
                num_odd_degree_v++;
        }
        if(num_odd_degree_v == 0 || num_odd_degree_v == 2)
            printf("Full\n");
        else 
            printf("Part\n");
    }

    destroy(dj_set);
    free(degrees);
    return 0;
}
