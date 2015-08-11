#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct Edge {
    int to;
    struct Edge *next;
} Edge;

Edge *create_edge(int to, Edge *next) {
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->to = to;
    e->next = next;
    return e;
}

typedef struct Graph {
    size_t vertex_num;
    int *in_degrees;
    Edge **adj_lists;
} Graph;

void destroy_graph(Graph *graph) {
    int i;
    for(i = 0; i < graph->vertex_num; i++) {
        Edge *edge = graph->adj_lists[i];
        while(edge != NULL) {
            Edge *temp = edge->next;
            free(edge);
            edge = temp;
        }
    }
    free(graph->adj_lists);
    free(graph->in_degrees);
    free(graph);
}

void decrease_indegree(Graph *graph, int from) {
    graph->in_degrees[from] -= 1;
    Edge *edge = graph->adj_lists[from];
    while(edge != NULL) {
        Edge *temp = edge->next;
        int to = edge->to;
        graph->in_degrees[to] -= 1;
        if(graph->in_degrees[to] == 0) {
            decrease_indegree(graph, to);
        }
        edge = temp;
    }
}

bool is_dag(Graph *graph) {
    int i;
    for(i = 0; i < graph->vertex_num; i++) {
        if(graph->in_degrees[i] == 0) {
            decrease_indegree(graph, i);
        }
    }
    for(i = 0; i < graph->vertex_num; i++) {
        if(graph->in_degrees[i] >= 0) 
            return false;
    }
    return true;
}

int main(void) {
    int T;
    scanf("%d", &T);
    int i;
    for(i = 0; i < T; i++) {
        Graph *graph = (Graph *)malloc(sizeof(Graph));
        int vertex_num, edge_num;
        scanf("%d %d", &vertex_num, &edge_num);
        graph->vertex_num = vertex_num;
        graph->in_degrees = (int *)malloc(sizeof(int) * graph->vertex_num);
        memset(graph->in_degrees, 0, sizeof(int) * graph->vertex_num);
        graph->adj_lists = (Edge **)malloc(sizeof(Edge *) * graph->vertex_num);
        memset(graph->adj_lists, 0, sizeof(Edge *) * graph->vertex_num);
        int k;
        for(k = 0; k < edge_num; k++) {
            int from, to;
            scanf("%d %d", &from, &to);
            from--; to--;
            Edge *edge = create_edge(to, graph->adj_lists[from]);
            graph->adj_lists[from] = edge;
            graph->in_degrees[to] += 1;
        }
        if(is_dag(graph)) {
            printf("Correct\n");
        }
        else {
            printf("Wrong\n");
        }
        destroy_graph(graph);
    }
    return 0;
}
