#ifndef _WDGRAPH_H_
#define _WDGRAPH_H_

#include "../ita.h"

struct edge {
    size_t from;
    size_t to;
    double weight;
    struct edge *next;
};
typedef struct edge Edge;
typedef Edge * PEdge;
typedef PEdge AdjList;

struct wdgraph {
    size_t vertex_num;
    size_t edge_num;
    PEdge *adjs;
};
typedef struct wdgraph * PWdgraph;

PWdgraph init_graph(FILE *stream);
void print_graph(PWdgraph g);
void destroy_graph(PWdgraph g);
bool contains_loop(PWdgraph g);
double shortest_path(PWdgraph g, int v, int w);

#endif
