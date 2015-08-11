#ifndef _WGRAPH_H_
#define _wGRAPH_H_

struct Edge {
    int v;
    int w;
    double weight;
};
typedef struct Edge Edge;
typedef struct Edge *PEdge;

struct wGraph {
    int vertex_num;
    int edge_num;
    Edge *edges;
};
typedef struct wGraph wGraph;

wGraph *init_graph_from_file(char *file_name);
PEdge *kruskal_mst(wGraph *wg);
PEdge *prim_mst(wGraph *wg);
void to_string(wGraph *wg);
void destroy_graph(wGraph *wg);


typedef struct PriorityQueue *PPQueue;
PPQueue buildPQueue(wGraph *wg);
PEdge delete_min(PPQueue pq);
void destroy_pqueue(PPQueue pq);
bool is_pqueue_empty(PPQueue pq);
int pqueue_size(PPQueue pq);

typedef struct IndexedPriorityQueue * PIPQ;
PIPQ init_indexed_priority_queue(size_t capacity);
bool ipq_contains(PIPQ ipq, int w);
double ipq_get_weight(PIPQ ipq, int w);
void ipq_insert(PIPQ ipq, PEdge edge);
PEdge ipq_delete_min(PIPQ ipq);
void ipq_decrease_weight(PIPQ ipq, int index, PEdge edge);
void ipq_to_string(PIPQ ipq);
void ipq_destroy(PIPQ ipq);
bool ipq_is_empty(PIPQ ipq);

#endif
