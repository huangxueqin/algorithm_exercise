#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXV 12
int nv, ne;
unsigned edges[MAXV];
int pv[(1 << MAXV)+1];
int count;

void dfs(int u, unsigned unused) {
    unused &= ~(1 << u);
    if(!unused) {
        if(edges[u] & 1) 
            count++;
    }
    else {
        unsigned unused_edges = edges[u] & unused;
        while(unused_edges) {
            int v = pv[unused_edges & (-unused_edges)];
            dfs(v, unused);
            unused_edges &= ~(unused_edges & (-unused_edges));
        }
    }
    unused |= (1 << u);
}

int main(void) {
    scanf("%d %d", &nv, &ne);
    int i, u, v;
    for(i = 0; i < MAXV; i++) edges[i] = 0u;
    for(i = 0; i < MAXV; i++) pv[1 << i] = i;
    for(i = 0; i < ne; i++) {
        scanf("%d %d", &u, &v);
        u--; v--;
        edges[u] |= (1 << v);
    }
    count = 0;
    unsigned unused = (1 << nv) - 1;
    dfs(0, unused);
    printf("%d\n", count);
    
    return 0;
}

