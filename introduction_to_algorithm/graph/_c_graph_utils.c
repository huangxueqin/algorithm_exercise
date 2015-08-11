#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include "_c_graph.h"
#include "_c_graph_utils.h"
#include "queue.h"
#include "stack.h"


inline void *malloc_array(size_t size, size_t len)
{
    void *p = (void *)malloc(len * size);
    if(p == NULL)
    {
        fprintf(stderr, "malloc array failed\n");
        return NULL;
    }
    memset(p, 0, len * size);
    return p;
}

void _dfs(Graph *g, int s, bool visited[], int edgeTo[])
{
    visited[s] = true;
    AdjNode *adj = g->adjs[s];
    while(adj != NULL)
    {
        if(!visited[adj->u])
        {
            edgeTo[adj->u] = s;
            _dfs(g, adj->u, visited, edgeTo);
        }
        adj = adj->next;
    }
}

void dfs(Graph *g, int s, int edgeTo[])
{
    bool *marked = (bool *)malloc(sizeof(bool) * g->vertexNum);
    memset(marked, 0, sizeof(bool) * g->vertexNum);
    edgeTo[s] = -1;
    _dfs(g, s, marked, edgeTo);
    free(marked);
} 

void _bfs(Graph *g, int s, int dist[], __queue *q)
{
    int cur_dist = dist[s];
    AdjNode *adj = g->adjs[s];
    while(adj != NULL)
    {
        if(dist[adj->u] < 0)
        {
            dist[adj->u] = cur_dist + 1;
            enqueue(q, adj);
        }
        adj = adj->next;
    }
}

void bfs(Graph *g, int s, int dist[])
{
    int i;
    __queue *queue = init_queue();
    for(i=0;i<g->vertexNum;i++)
    {
        dist[i] = -1;
    }
    dist[s] = 0;
    _bfs(g, s, dist, queue);
    while(!is_queue_empty(queue))
    {
        AdjNode *edge = (AdjNode *)dequeue(queue);
        _bfs(g, edge->u, dist, queue);
    }
    destroy_queue(queue);
}

void reverse_top_sort_array(int array[], int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        array[i] = len - 1 - array[i];
    }
}

void _top_sort(Graph *g, int s, int result[], int *rank)
{
    if(result[s] >= 0)
        return;
    AdjNode *adj = g->adjs[s];
    while(adj != NULL)
    {
        if(result[adj->u] < 0)
            _top_sort(g, adj->u, result, rank);
        adj = adj->next;
    }
    result[s] = *(rank);
    *rank = *rank + 1;
}

void top_sort(Graph *g, int suggest_start, int result[])
{
    int rank = 0;
    int i, len = g->vertexNum;
    for(i=0;i<len;i++)
    {
        result[i] = -1;
    }
    for(i=0;i<len && i < suggest_start;i++)
    {
            _top_sort(g, i, result, &rank);
    }

    for(i=suggest_start + 1;i<len;i++) {
            _top_sort(g, i, result, &rank);
    }
    _top_sort(g, suggest_start, result, &rank);
    reverse_top_sort_array(result, len);
}

void _sc_dfs1(Graph *g, int v, bool marked[], STACK s) {
    marked[v] = true;
    AdjNode *adj = g->adjs[v];
    while(adj != NULL)
    {
        if(!marked[adj->u])
            _sc_dfs1(g, adj->u, marked, s);
        adj = adj->next;
    }
    iStack.push(s, &v);
}

void _sc_dfs2(Graph *g, int s, bool marked[], int *groupNum, int group[])
{
    marked[s] = true;
    group[s] = *groupNum;
    AdjNode *adj = g->adjs[s];
    while(adj != NULL) {
        if(!marked[adj->u]) {
            _sc_dfs2(g, adj->u, marked, groupNum, group);
        }
        adj = adj->next;
    }
}

void strong_component(Graph *g, int groups[])
{
    Graph *rg = reverse(g);
    STACK s = iStack.init_stack(sizeof(int));
    int len = g->vertexNum;
    bool *marked = (bool *)malloc_array(sizeof(bool), len);
    int i;
    for(i=0;i<len;i++)
        marked[i] = false;
    
    for(i=0;i<len;i++)
        if(!marked[i])
            _sc_dfs1(rg, i, marked, s);

    int v;
    int groupNum = 0;
    for(i=0;i<len;i++) marked[i] = false;
    while(!iStack.is_empty(s))
    {
        iStack.pop(s, &v);
        if(!marked[v]) {
            _sc_dfs2(g, v, marked, &groupNum, groups);
            groupNum++;
        }
    }
    free(marked);
    destroy(rg);
    iStack.destroy(s);
}
