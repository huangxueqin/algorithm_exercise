#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct edge {
    int v;
    struct edge *next;
};

struct graph {
    size_t num_vertex;
    struct edge* *edge_lists;
};

struct edge *create_edge(int v, struct edge *next) {
    struct edge *edge = (struct edge *) malloc(sizeof(struct edge));
    memset(edge, 0, sizeof(struct edge));
    edge->v = v;
    edge->next = next;
    return edge;
}

struct graph *create_graph(size_t n) {
    struct graph *graph = (struct graph *) malloc(sizeof(struct graph));
    memset(graph, 0, sizeof(struct graph));
    graph->num_vertex = n;
    graph->edge_lists = (struct edge* *) malloc(sizeof(char *) * n);
    memset(graph->edge_lists, 0, sizeof(char *) * n);
    return graph;
}

void free_edge_list(struct edge *edge_list) {
    while(edge_list) {
        struct edge *next = edge_list->next;
        free(edge_list);
        edge_list = next;
    }
}

void free_graph(struct graph *graph) {
    int i;
    for(i = 0; i < graph->num_vertex; i++) {
        free_edge_list(graph->edge_lists[i]);
    }
    free(graph->edge_lists);
    free(graph);
}

int get_hamiltonian_cycle_num(struct graph *graph);

int states[12][4096];

int main(void) {
    int num_vertex, num_edge;
    scanf("%d %d", &num_vertex, &num_edge);
    struct graph *graph = create_graph(num_vertex);
    int i, u, v;
    for(i = 0; i < num_edge; i++) {
        scanf("%d %d", &u, &v);
        u--; v--;
        graph->edge_lists[u] = create_edge(v, graph->edge_lists[u]);
    }
    printf("%d\n", get_hamiltonian_cycle_num(graph));
    free_graph(graph);
    return 0;
}

int edge_to(const struct graph *graph, const int u, const int v) {
    struct edge *p = graph->edge_lists[u];
    while(p) {
        if(p->v == v) return 1;
        p = p->next;
    }
    return 0;
}

int dfs(const struct graph *graph, const int u, int *visit, int num_visted, int states[][4096], int prev_state) {
    if(states[u][prev_state] == -1) {
        int cur_state = ((1 << u) | prev_state);
        visit[u] = 1;
        num_visted++;
        if(num_visted == graph->num_vertex) {
            // judge that if we can reach vertex 0
            if(edge_to(graph, u, 0)) 
                states[u][prev_state] = 1;
        }
        else {
            int result = 0;
            struct edge *p = graph->edge_lists[u];
            while(p) {
                int v = p->v;
                if(!visit[v]) {
                    result += dfs(graph, v, visit, num_visted, states, cur_state);
                }
                p = p->next;
            }
            states[u][prev_state] = result;
        }
        visit[u] = 0;
    }
    return states[u][prev_state];
}

int get_hamiltonian_cycle_num(struct graph *graph) {
    int *visit = (int *) malloc(sizeof(int) * graph->num_vertex);
    memset(visit, 0, sizeof(int) * graph->num_vertex);
    memset(states, -1, sizeof(states));
    int count = dfs(graph, 0, visit, 0, states, 0);
    free(visit);
    return count;
}

/* void dfs(const struct graph *graph, const int u, int *count,
 *         int *visit, int num_visted, int states[][4096], int prev_state) {
 *     if(states[u][prev_state] == -1) {
 *         int cur_state = ((1 << u) | prev_state);
 *         int saved_count = *count;
 *         visit[u] = 1;
 *         num_visted++;
 *         if(num_visted == graph->num_vertex) {
 *             // judge that if we can reach vertex 0
 *             if(edge_to(graph, u, 0)) 
 *                 (*count) += 1;
 *         }
 *         else {
 *             struct edge *p = graph->edge_lists[u];
 *             while(p) {
 *                 int v = p->v;
 *                 if(!visit[v]) {
 *                     dfs(graph, v, count, visit, num_visted, states, cur_state);
 *                 }
 *                 p = p->next;
 *             }
 *         }
 *         states[u][prev_state] = (*count) - saved_count;
 *         visit[u] = 0;
 *     }
 *     else {
 *         (*count) += states[u][prev_state];
 *     }
 * }
 * 
 * int get_hamiltonian_cycle_num(struct graph *graph) {
 *     int count = 0;
 *     int *visit = (int *) malloc(sizeof(int) * graph->num_vertex);
 *     memset(visit, 0, sizeof(int) * graph->num_vertex);
 *     memset(states, -1, sizeof(states));
 *     dfs(graph, 0, &count, visit, 0, states, 0);
 *     free(visit);
 *     return count;
 * } */
