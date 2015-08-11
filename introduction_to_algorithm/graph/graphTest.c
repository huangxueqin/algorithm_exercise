#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "_c_graph.h"

int main(int argc, char *argv[])
{
    Graph *g;
    char *s;
    /*
       int vertexNum, edgeNum, v, w;
       AdjNode **adjs;

       printf("input number of vertices and edges: \n");
       scanf("%d %d", &vertexNum, &edgeNum);

       adjs = (AdjNode **)malloc(vertexNum * sizeof(AdjNode *));
       memset(adjs, 0, vertexNum * sizeof(AdjNode *));

       printf("input edges: \n");
       while(scanf("%d %d", &v, &w) != EOF)
       {
       AdjNode *node = (AdjNode *)malloc(sizeof(AdjNode));
       node->u = w;
       AdjNode *adj = adjs[v];
       if(adj != NULL)
       {
       node->next = adj;
       }
       adjs[v] = node;
       }
       g = init_graph(vertexNum, edgeNum, adjs);
       */

    if(argc < 2)
    {
        printf("provide file path\n");
        exit(EXIT_FAILURE);
    }
    g = init_graph_from_file(argv[1]);
    if(g != NULL)
    {
        s = to_string(g);
        printf("g is:\n%s", s);
        destroy(g);
        free(s);

    }
    else
        printf("init graph from file failed\n");
    return 0;
}
