#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <cstddef>
#include <iostream>

struct AdjNode {
    int to;
    int weight;
    int capacity;
    int cost;
    AdjNode *next;
    AdjNode(int v);
    AdjNode(int v, int weight);
    AdjNode(int v, int weight, int capacity);
    AdjNode(int v, int weight, int capacity, int cost);
    AdjNode(int v, AdjNode *next);
    AdjNode(int v, int weight, AdjNode *next);
    AdjNode(int v, int weight, int capacity, AdjNode *next);
    AdjNode(int v, int weight, int capacity, int cost, AdjNode *next);
};

struct Edge {
        int from;
        int to;
        int weight;
        int capacity;
        int cost;
        Edge(int from, int to);
        Edge(int from, int to, int weight);
        Edge(int from, int to, int weight, int capacity);
        Edge(int from, int to, int weight, int capacity, int cost);
};

// graph using adjucent list
struct Graph {
    std::size_t num_vertices;
    std::size_t num_edges;
    AdjNode **adjlists;

    Graph(int num_vertices, int num_edges, std::pair<int, int> edges[]);
    Graph(int num_vertices, int num_edges, Edge edges[]);
    ~Graph();
};

struct UndirectedEdge {
    int v1;
    int v2;
    double weight;
    UndirectedEdge(int v1, int v2);
    UndirectedEdge(int v1, int v2, double weight);
};

// graph using edges
struct UndirectedEdgedGraph {
    std::size_t num_vertices;
    std::size_t num_edges;
    UndirectedEdge *edges;

    UndirectedEdgedGraph(size_t num_vertices, size_t num_edges, UndirectedEdge *edges);
    ~UndirectedEdgedGraph();
};

#endif
