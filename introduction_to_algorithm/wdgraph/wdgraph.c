#include <float.h>
#include <math.h>
#include "wdgraph.h"
#include "../ita.h"
#define __debug 1


/*********************************************************************
 ************************data structures******************************
 *********************************************************************/

/*************************IndexedPriorityQueue************************/
struct IPQ_elmt {
    size_t v;
    double dist;
};
typedef struct IPQ_elmt *PIPQ_elmt;

PIPQ_elmt _malloc_IPQ_elmt(size_t v, double dist) {
    PIPQ_elmt ipq_elmt = (PIPQ_elmt)malloc(sizeof(struct IPQ_elmt));
    ipq_elmt->v = v;
    ipq_elmt->dist = dist;
    return ipq_elmt;
}

struct IndexedPriorityQueue {
    size_t arr_size;
    size_t cur_size;
    int *indices;
    PIPQ_elmt *elmts;
};
typedef struct IndexedPriorityQueue IndexedPriorityQueue;
typedef struct IndexedPriorityQueue *PIndexedPriorityQueue;

/* init indexed priority queue */
PIndexedPriorityQueue ipq_init(size_t max_size) {
    PIndexedPriorityQueue ipq = (PIndexedPriorityQueue)malloc(sizeof(IndexedPriorityQueue));
    ipq->arr_size = max_size;
    ipq->cur_size = 0;
    ipq->indices = (int *)malloc(sizeof(int) * max_size);
    ipq->elmts = (PIPQ_elmt *)malloc(sizeof(PIPQ_elmt) * (max_size+1));
    memset(ipq->indices, 0, sizeof(int) * max_size);
    memset(ipq->elmts, 0, sizeof(PIPQ_elmt) * (max_size + 1));
    return ipq;
}

/* destroy indexed priority queue */
void ipq_destroy(PIndexedPriorityQueue ipq) {
    if(ipq != NULL) {
        for(int i=0;i<ipq->arr_size;i++)
            if(ipq->elmts[i] != NULL)
                free(ipq->elmts[i]);
        free(ipq->elmts);
        free(ipq->indices);
    }
    free(ipq);
}

bool ipq_contains_vertex(PIndexedPriorityQueue ipq, int v) {
    return ipq->indices[v] != 0;
}

void swap_position(PIPQ_elmt *elmt, int p, int q) {
    PIPQ_elmt t = elmt[p];
    elmt[p] = elmt[q];
    elmt[q] = t;
}

int ipq_flow_up(PIndexedPriorityQueue ipq, int index) {
    int c = index;
    if(c <= 1) return c;
    if(ipq->elmts[c/2]->dist > ipq->elmts[c]->dist) {
        swap_position(ipq->elmts, c/2, c);
        ipq->indices[ipq->elmts[c]->v] = c;
        return ipq_flow_up(ipq, c/2);
    }
    else 
        return c;
}

/* insert vertex into queue */
void ipq_insert(PIndexedPriorityQueue ipq, PIPQ_elmt ipq_elmt) {
    ipq->cur_size++;
    ipq->elmts[ipq->cur_size] = ipq_elmt;
    ipq->indices[ipq_elmt->v] = ipq_flow_up(ipq, ipq->cur_size);
}

int ipq_flow_down(PIndexedPriorityQueue ipq, int index) {
    int p = index;
    if(2*p > ipq->cur_size) return p;
    int left = 2 * p;
    int right = left + 1 > ipq->cur_size ? left : left + 1;
    int c = ipq->elmts[left]->dist < ipq->elmts[right]->dist ? left : right;
    if(ipq->elmts[p]->dist > ipq->elmts[c]->dist) {
        swap_position(ipq->elmts, p, c);
        ipq->indices[ipq->elmts[p]->v] = p;
        return ipq_flow_down(ipq, c);
    }
    else
        return p;
}

/* delete min from queue */
PIPQ_elmt ipq_delete_min(PIndexedPriorityQueue ipq) {
    if(ipq->cur_size == 0) return NULL;
    PIPQ_elmt min = ipq->elmts[1];
    ipq->elmts[1] = ipq->elmts[ipq->cur_size];
    ipq->indices[ipq->elmts[ipq->cur_size]->v] = 0;
    ipq->elmts[ipq->cur_size] = NULL;
    ipq->cur_size--;
    ipq->indices[min->v] = ipq->cur_size == 0 ? 0 : ipq_flow_down(ipq, 1);
    return min;
}

/* decrease node's key in queue */
void ipq_decrease_vertex(PIndexedPriorityQueue ipq, int v, int ddist) {
    ipq->elmts[ipq->indices[v]]->dist = ddist;
    ipq->indices[v] = ipq_flow_down(ipq, ipq->indices[v]);
}

bool ipq_is_empty(PIndexedPriorityQueue ipq) {
    return ipq->cur_size == 0;
}

/**********************data structures end***************************/

PEdge _malloc_edge(size_t from, size_t to, double weight, PEdge next) {
    PEdge edge = (PEdge)malloc(sizeof(Edge));
    memset(edge, 0, sizeof(Edge));
    edge->from = from;
    edge->to = to;
    edge->weight = weight;
    edge->next = next;
    return edge;
}

PWdgraph _malloc_graph(size_t vertex_num, size_t edge_num) {
    PWdgraph graph = (PWdgraph)malloc(sizeof(struct wdgraph));
    memset(graph, 0, sizeof(struct wdgraph));
    graph->vertex_num = vertex_num;
    graph->edge_num = edge_num;
    graph->adjs = (PEdge *)malloc(sizeof(PEdge) * vertex_num);
    memset(graph->adjs, 0, sizeof(PEdge) * vertex_num);
    return graph;
}

/* init graph */
PWdgraph init_graph(FILE *fp) {
    size_t v, w, vertex_num, edge_num;
    double weight;

    fscanf(fp, "%zu", &(vertex_num));
    fscanf(fp, "%zu", &(edge_num));
    PWdgraph g = _malloc_graph(vertex_num, edge_num);
    for(int i=0;i<g->edge_num;i++) {
        if(EOF == fscanf(fp, "%zu%zu%lf", &v, &w, &weight)) {
            destroy_graph(g);
            return NULL;
        }
        PEdge edge = _malloc_edge(v, w, weight, g->adjs[v]);
        g->adjs[v] = edge;
    }

    return g;
}

/* print graph */
void print_graph(PWdgraph g) {
    printf("%zu\n", g->vertex_num);
    printf("%zu\n", g->edge_num);
    for(int i=0;i<g->vertex_num;i++) {
        printf("%d: ", i);
        AdjList adj = g->adjs[i];
        while(adj != NULL) {
            printf("%zu(%lf)", adj->to, adj->weight);
            if(adj->next != NULL)
                printf(", ");
            adj = adj->next;
        }
        printf(";\n");
    }
}

/* destroy graph */
void destroy_graph(PWdgraph g) {
    AdjList *adjs = g->adjs;
    for(int i=0;i<g->vertex_num;i++) {
        PEdge edge = adjs[i];
        while(edge != NULL) {
            PEdge tmp = edge;
            edge = edge->next;
            free(tmp);
        }
    }
    free(adjs);
    free(g);
}

/* judge if the graph contains loop(s) */
#define WHITE 0
#define GREY  1
#define BLACK 2
typedef int Color;
bool _dfs(PWdgraph g, int v, Color *c);

bool contains_loop(PWdgraph g) {
    int num = g->vertex_num;
    Color *c = (Color *)malloc(sizeof(Color) * num);
    memset(c, 0, sizeof(Color) * num);
    for(int i=0;i<num;i++)
        if(c[i] == WHITE)
            if(_dfs(g, i, c))
                return true;
    return false;
}

bool _dfs(struct wdgraph *g, int v, Color *c) {
    c[v] = GREY;
    PEdge edge = g->adjs[v];
    while(edge != NULL) {
        size_t w = edge->to;
        if(c[w] == GREY)
            return true;
        else if(c[w] == WHITE)
            if(_dfs(g, w, c))
                return true;
        edge = edge->next;
    }
    c[v] = BLACK;
    return false;
}

/* Shortest path */
#define DIJKSTRA 0x1
#define SP_METHOD DIJKSTRA
double _dijkstra_sp(PWdgraph g, int v, int w);

double shortest_path(PWdgraph g, int v, int w) {
    double sp = 0.0;
#if SP_METHOD == DIJKSTRA
    sp = _dijkstra_sp(g, v, w);
#endif
    return sp;
}

void relax_vertices(PWdgraph g, int v, PIndexedPriorityQueue ipq, double dists[]) {
    AdjList adj = g->adjs[v];
    while(adj != NULL) {
        PEdge edge = adj;
        if(dists[v] + edge->weight < dists[edge->to]) {
            dists[edge->to] = dists[v] + edge->weight;
            if(ipq_contains_vertex(ipq, edge->to))
                ipq_decrease_vertex(ipq, edge->to, dists[edge->to]);
            else
                ipq_insert(ipq, _malloc_IPQ_elmt(edge->to, dists[edge->to]));
        }
        adj = adj->next;
    }
}

double _dijkstra_sp(PWdgraph g, int v, int w) {
    PIndexedPriorityQueue ipq = ipq_init(g->vertex_num);
    double *dists = (double *)malloc(sizeof(double) * g->vertex_num);
    for(int i=0;i<g->vertex_num;i++) dists[i] = DBL_MAX;
    dists[v] = 0;
    ipq_insert(ipq, _malloc_IPQ_elmt(v, 0));
    while(!ipq_is_empty(ipq)) {
        PIPQ_elmt e = ipq_delete_min(ipq);
        relax_vertices(g, e->v, ipq, dists);
        free(e);
    }
    ipq_destroy(ipq);
    return dists[w];
}
