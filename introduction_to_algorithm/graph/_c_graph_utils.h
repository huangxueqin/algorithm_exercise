#ifndef __C_GRAPH_UTILS_H_
#define __C_GRAPH_UTILS_H_

#include "_c_graph.h"

//unweighted
void dfs(Graph *g, int s, int edgeTo[]);
void bfs(Graph *g, int s, int dist[]);
void top_sort(Graph *g, int suggest_start, int result[]);
#endif
