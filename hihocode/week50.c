#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1010

int graph[MAXN][MAXN];
int degree[MAXN];
int path[MAXN*10];
int path_size;
int M, N;

int find_start_vertex() {
    int i;
    int start = -1;
    for(i = 1; i <= N; i++)
        if(degree[i] & 0x1) {
            start = i;
            break;
        }
    if(start < 0) {
        for(i = 1; i <= N; i++) {
            if(degree[i] > 0) {
                start = i;
                break;
            }
        }
    }
    return start;
}

void delete_edge(int u, int v) {
    graph[u][v]--;
    graph[v][u]--;
}

int find_adjacent_vertex(int u) {
    int i;
    int adj = -1;
    for(i = 1; i <= N; i++)
        if(graph[u][i] > 0) {
            adj = i;
            break;
        }
    return adj;
}

int main(void) {
    memset(graph, 0, sizeof(graph));
    memset(degree, 0, sizeof(degree));
    scanf("%d %d", &N, &M);
    int i;
    for(i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        degree[u]++;
        degree[v]++;
        graph[u][v]++;
        graph[v][u]++;
    }
    int start = find_start_vertex();
    path_size = 0;
    path[path_size++] = start;
    while(path_size > 0) {
        int next = find_adjacent_vertex(start);
        if(next > 0) {
            delete_edge(start, next);
            path[path_size++] = next;
            start = next;
        }
        else {
            printf("%d", start);
            path_size--;
            if(path_size <= 0) break;
            printf(" ");
            start = path[path_size-1];
        }
    }
    return 0;
}
