#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "wgraph.h"


/**
 * DisjointSet implementation
 */
struct DisjointSet {
    int set_num;
    int *parent;
    int *rank;
};
typedef struct DisjointSet DisjointSet;

DisjointSet *init_disjoint_set(int n) {
    DisjointSet *d = (DisjointSet *)malloc(sizeof(DisjointSet));
    d->set_num = n;
    d->parent = (int *)malloc(sizeof(int) * n);
    int i;
    for(i=0;i<n;i++)
        d->parent[i] = i;
    d->rank = (int *)malloc(sizeof(int) * n);
    memset(d->rank, 0, n * sizeof(int));
    return d;
}

int find(DisjointSet *ds, int x) {
    if(ds->parent[x] != x) 
        ds->parent[x] = find(ds, ds->parent[x]);
    return ds->parent[x];
}

bool same_set(DisjointSet *ds, int x, int y) {
    return find(ds, x) == find(ds, y);
}

void unite(DisjointSet *ds, int x, int y) {
    x = find(ds, x);
    y = find(ds, y);
    if(same_set(ds, x, y))
        return;
    if(ds->rank[x] < ds->rank[y])
        ds->parent[x] = y;
    else {
        ds->parent[y] = x;
        if(ds->rank[y] == ds->rank[x])
            ds->rank[x]++;
    }
}

void destroy_disj(DisjointSet *ds) {
    free(ds->parent);
    free(ds->rank);
    free(ds);
}


/**
 * simple PriorityQueue implementation
 */
struct PriorityQueue {
    int capacity;
    int size;
    PEdge *edge_arr;
};

typedef struct PriorityQueue PQueue;
void to_string_pqueue(PQueue *pq);
void flowdown(PQueue *pq, int x);

void init_priority_queue(PQueue *pq) {
    int capacity = pq->capacity;
    int i;
    for(i=capacity/2;i>0;i--) {
        double pw = pq->edge_arr[i]->weight;
        double lw = pq->edge_arr[i*2]->weight;
        double rw = lw;
        if(i*2 < capacity)
            rw = pq->edge_arr[i*2+1]->weight;
        if(rw < lw && rw < pw) {
            PEdge tmp = pq->edge_arr[i];
            pq->edge_arr[i] = pq->edge_arr[i*2+1];
            pq->edge_arr[i*2+1] = tmp;
            flowdown(pq, i*2+1);
        }
        else {
            if(lw < pw) {
                PEdge tmp = pq->edge_arr[i];
                pq->edge_arr[i] = pq->edge_arr[2*i];
                pq->edge_arr[2*i] = tmp;
                flowdown(pq, i*2);
            }
        }
    }
}


PQueue *buildPQueue(wGraph *wg) {
    PQueue *pq = (PQueue *)malloc(sizeof(PQueue));
    pq->capacity = wg->edge_num;
    pq->size = pq->capacity;
    pq->edge_arr = (PEdge *)malloc(sizeof(PEdge) * (pq->capacity + 1));
    pq->edge_arr[0] = NULL;
    int ec;
    for(ec=0;ec<pq->capacity;ec++)
        pq->edge_arr[ec+1] = wg->edges+ec;
    init_priority_queue(pq);
    return pq;
}

void flowdown(PQueue *pq, int x) {
    int left = 2*x;
    int right = 2*x+1;
    double lw, rw, pw;
    if(x <= pq->size)
        pw = pq->edge_arr[x]->weight;
    if(left <= pq->size) {
        lw = pq->edge_arr[left]->weight;
        if(right <= pq->size)
            rw = pq->edge_arr[right]->weight;
        else
            rw = lw;
        if(rw < lw && rw < pw) {
            PEdge tmp = pq->edge_arr[x];
            pq->edge_arr[x] = pq->edge_arr[right];
            pq->edge_arr[right] = tmp;
            flowdown(pq, right);
        }
        else {
            if(lw < pw) {
                PEdge tmp = pq->edge_arr[x];
                pq->edge_arr[x] = pq->edge_arr[left];
                pq->edge_arr[left] = tmp;
                flowdown(pq, left);
            }
        }
    }
}

PEdge delete_min(PQueue *pq) {
    if(pq->size < 1)
        return NULL;
    PEdge min = pq->edge_arr[1];
    pq->edge_arr[1] = pq->edge_arr[pq->size];
    pq->size--;
    flowdown(pq, 1);
    return min;
}

bool is_pqueue_empty(PQueue *pq) {
    return pq->size == 0;
}

int pqueue_size(PQueue *pq) {
    return pq->size;
}

void to_string_pqueue(PQueue *pq) {
    int i;
    for(i=1;i<=pq->size;i++) {
        Edge *e = pq->edge_arr[i];
        printf("%d->%d: %lf\n", e->v, e->w, e->weight);
    }
}

void destroy_pqueue(PQueue *pq) {
    free(pq->edge_arr);
    free(pq);
}


/**
 * implementation of Indexed PriorityQueue
 */
struct IndexedPriorityQueue {
    size_t capacity;
    size_t cur_size;
    int *index_array;
    PEdge *edge_heap;
};

typedef struct IndexedPriorityQueue IndexedPriorityQueue;

IndexedPriorityQueue *init_indexed_priority_queue(size_t capacity) {
    IndexedPriorityQueue *ipq = (IndexedPriorityQueue *)malloc(sizeof(IndexedPriorityQueue));
    ipq->capacity = capacity;
    ipq->cur_size = 0;
    ipq->index_array = (int *)malloc(capacity * sizeof(int));
    memset(ipq->index_array, 0, capacity * sizeof(int));
    ipq->edge_heap = (PEdge *)malloc((1 + capacity) * sizeof(PEdge));
    memset(ipq->edge_heap, 0, (1 + capacity) * sizeof(PEdge));
    return ipq;
};

bool ipq_contains(IndexedPriorityQueue *ipq, int w) {
    return ipq->index_array[w] != 0;
}

double ipq_get_weight(IndexedPriorityQueue *ipq, int w) {
    return ipq->edge_heap[ipq->index_array[w]]->weight;
}

void swap(PEdge *edges, int x, int y) {
    PEdge tmp = edges[x];
    edges[x] = edges[y];
    edges[y] = tmp;
}

int ipq_flow_up(IndexedPriorityQueue *ipq, int x) {
    int p = x/2;
    if(p > 0 && ipq->edge_heap[p]->weight > ipq->edge_heap[x]->weight) {
        swap(ipq->edge_heap, p, x);
        return ipq_flow_up(ipq, p);
    }
    else {
        return x;
    }
}

void ipq_insert(IndexedPriorityQueue *ipq, PEdge edge, int w) {
    ++ipq->cur_size;
    ipq->edge_heap[ipq->cur_size] = edge;
    ipq->index_array[w] = ipq_flow_up(ipq, ipq->cur_size);
}

int ipq_flow_down(IndexedPriorityQueue *ipq, int x) {
    int left = x * 2;
    int right = x * 2 + 1;
    double pw = ipq->edge_heap[x]->weight, lw, rw;
    if(left <= ipq->cur_size) {
        rw = lw = ipq->edge_heap[left]->weight;
        if(right <= ipq->cur_size)
            rw = ipq->edge_heap[right]->weight;
        if(rw < lw && rw < pw) {
            swap(ipq->edge_heap, x, right);
            return ipq_flow_down(ipq, right);
        }
        else if(lw < pw) {
            swap(ipq->edge_heap, x, left);
            return ipq_flow_down(ipq, left); 
        }
    }
    return x;
}

PEdge ipq_delete_min(IndexedPriorityQueue *ipq) {
    PEdge edge = ipq->edge_heap[1];
    ipq->index_array[edge->w] = 0;
    ipq->edge_heap[1] = ipq->edge_heap[ipq->cur_size];
    ipq->cur_size--;
    ipq->index_array[ipq->edge_heap[1]->w] = ipq_flow_down(ipq, 1);
    return edge;
}

void ipq_decrease_weight(IndexedPriorityQueue *ipq, int index, PEdge edge) {
    ipq->edge_heap[ipq->index_array[index]] = edge;
    ipq->index_array[index] = ipq_flow_up(ipq, ipq->index_array[index]);
}

void ipq_to_string(IndexedPriorityQueue *ipq) {
    int i;
    for(i=1;i<=ipq->cur_size;i++) {
        PEdge edge = ipq->edge_heap[i];
        printf("%d->%d: %lf\n", edge->v, edge->w, edge->weight);
    }
}

bool ipq_is_empty(IndexedPriorityQueue *ipq) {
    return ipq->cur_size == 0;
}

void ipq_destroy(IndexedPriorityQueue *ipq) {
    free(ipq->index_array);
    free(ipq->edge_heap);
    free(ipq);
}

/**
 * wGraph functions implementation
 */
inline Edge *malloc_edge(int v, int w, double weight) {
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    edge->v = v;
    edge->w = w;
    edge->weight = weight;
    return edge;
}

char *next_positive_integer(char *ptr, int *num) {
    *num = 0;
    while(*ptr && isspace(*ptr)) ptr++;
    while(*ptr >= '0' && *ptr <= '9')
        *num = *num * 10 + (*ptr++ - '0');
    return ptr;
}

char *next_double(char *ptr, double *d) {
    double num = 0;
    int scale = 0;
    while(*ptr && isspace(*ptr)) ptr++;
    if(*ptr >= '0' && *ptr <= '9')
        do
            num = num * 10 + (*ptr++ - '0');
        while(*ptr <= '9' && *ptr >= '0');
    if(*ptr == '.' && ptr[1] >= '0' && ptr[1] <= '9') {
        ptr++;
        do {
            num = num * 10 + (*ptr++ - '0');
            scale--;
        }while(*ptr >= '0' && *ptr <= '9');
    }
    *d = num * pow(10.0, scale);
    return ptr;
}

int parse_vertex_num(char *buf, FILE *fp) {
    int vn; 
    next_positive_integer(buf, &vn);
    return vn;
}

int parse_edge_num(char *buf, FILE *fp) {
    return parse_vertex_num(buf, fp);
}

void parse_edge(char *buf, FILE *fp, PEdge e) {
    buf = next_positive_integer(buf, &(e->v));
    buf = next_positive_integer(buf, &(e->w));
    buf = next_double(buf, &(e->weight));
}

#define BUF_SIZE 42
wGraph *init_graph_from_file(char *file_name) {
    FILE *fp;
    char *buf = (char *)malloc(sizeof(char) * BUF_SIZE);;
    size_t n;
    int vertex_num, edge_num;
    if((fp = fopen(file_name, "r")) == NULL) {
        fprintf(stderr, "can't open file :%s\n", file_name);
        return NULL;
    }
    
    getline(&buf, &n, fp);
    vertex_num = parse_vertex_num(buf, fp);
    getline(&buf, &n, fp);
    edge_num = parse_edge_num(buf, fp);
    
    wGraph *wg = (wGraph *)malloc(sizeof(wGraph));
    wg->vertex_num = vertex_num;
    wg->edge_num = edge_num;
    wg->edges = (Edge *)malloc(edge_num * sizeof(Edge));
    memset(wg->edges, 0, sizeof(Edge) * edge_num);
   
    int ec = 0;
    while(ec < edge_num) {
        getline(&buf, &n, fp);
        parse_edge(buf, fp, wg->edges + ec); 
        ec++;
    }
    free(buf);
    fclose(fp);
    return wg;
}

void to_string(wGraph *g) {
    printf("wGraph is:\n");
    printf("%d\n", g->vertex_num);
    printf("%d\n", g->edge_num);
    int ec = 0;
    for(ec=0;ec<g->edge_num;ec++)
        printf("%d->%d : %lf\n", g->edges[ec].v, g->edges[ec].w, g->edges[ec].weight);
}

void destroy_graph(wGraph *g) {
    free(g->edges);
    free(g);
}


/**
 * Kruskal mst Alg.
 */
PEdge *kruskal_mst(wGraph *wg) {
    PEdge *edges = (PEdge *)malloc((wg->vertex_num-1) * sizeof(PEdge));
    PQueue *pq = buildPQueue(wg);
    DisjointSet *ds = init_disjoint_set(wg->vertex_num);
    int mst_edges = 0;
    while(mst_edges < wg->vertex_num - 1 && !is_pqueue_empty(pq)) {
        PEdge edge = delete_min(pq);
        int v = edge->v;
        int w = edge->w;
        if(!same_set(ds, v, w)) {
            unite(ds, v, w);
            edges[mst_edges] = edge;
            mst_edges++;
        }
    }
    destroy_pqueue(pq);
    destroy_disj(ds);
    return edges;
}


/**
 * Prim mst Alg.
 */
typedef struct AdjNode {
    PEdge edge;
    struct AdjNode *next;
} AdjNode , *PAdjNode;

void add_edge_in_adjs(PAdjNode *adjs, PEdge edge) {
    int v = edge->v;
    int w = edge->w;
    PAdjNode adjv = (PAdjNode)malloc(sizeof(AdjNode));
    PAdjNode adjw = (PAdjNode)malloc(sizeof(AdjNode));
    adjv->edge = edge;
    adjv->next = adjs[v];
    adjs[v] = adjv;
    adjw->edge = edge;
    adjw->next = adjs[w];
    adjs[w] = adjw;
}

int another(int v, PEdge edge) {
    int w = edge->w;
    if(v != w)
        return w;
    else 
        return edge->v;
}

void print_adjs(PAdjNode *adjs, size_t len) {
    int i;
    for(i=0;i<len;i++) {
        PAdjNode adj = adjs[i];
        printf("%d->", i);
        while(adj != NULL) {
            PEdge edge = adj->edge;
            printf("%d, ", another(i, edge));
            adj = adj->next;
        }
        printf("\n");
    }
}

void destroy_adjs(PAdjNode *adjs, size_t len) {
    int i;
    for(i=0;i<len;i++) {
        PAdjNode adj = adjs[i];
        while(adj != NULL) {
            PAdjNode tmp = adj->next;
            free(adj);
            adj = tmp;
        }
    }
    free(adjs);
}

PEdge *prim_mst(wGraph *wg) {
    PAdjNode *adjs = (PAdjNode *)malloc(sizeof(PAdjNode) * wg->vertex_num);
    memset(adjs, 0, sizeof(PAdjNode) * wg->vertex_num);
    int i;
    for(i=0;i<wg->edge_num;i++) {
        PEdge edge = wg->edges + i;
        add_edge_in_adjs(adjs, edge);
    }
    DisjointSet *ds = init_disjoint_set(wg->vertex_num);
    IndexedPriorityQueue *ipq = init_indexed_priority_queue(wg->vertex_num);
    PEdge *edge = malloc(sizeof(PEdge) * (wg->vertex_num - 1));
    int mst_count = 0;
    
    PAdjNode adj = adjs[0];
    while(adj != NULL) {
        ipq_insert(ipq, adj->edge



    destroy_disj(ds);
    ipq_destroy(ipq);
    destroy_adjs(adjs, wg->vertex_num);
    return NULL;
}

