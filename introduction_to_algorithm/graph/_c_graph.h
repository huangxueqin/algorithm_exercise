#ifndef __C_GRAPH_
#define __C_GRAPH_

struct AdjNode {
    int u;
    int weight;
    struct AdjNode *next;
};
typedef struct AdjNode AdjNode;

struct Graph {
    int vertexNum;
    int edgeNum;
    AdjNode **adjs;
};
typedef struct Graph Graph;

extern Graph *init_graph_no_edge(const int vNum);
extern Graph *init_graph(const int vNum, const int eNum, AdjNode **adjs);
extern Graph *init_graph_from_file(const char *path);
extern Graph *reverse(Graph *g);
extern void destroy(Graph *g);
extern void add_edge(Graph *g, int v, int w);
extern void add_2edge(Graph *g, int v, int w);
extern void add_wedge(Graph *g, int v, int w, int weight);
extern void add_w2edge(Graph *g, int v, int w, int weight);
extern char *to_string(const Graph *g);
extern char *to_wstring(const Graph *g);
#endif
