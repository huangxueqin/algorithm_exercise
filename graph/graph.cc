#include <iostream>
#include <cstdio>
#include <cstring>
#include "graph.h"

// member functions of AdjNode
AdjNode::AdjNode(int v) : 
    to(v), weight(1), capacity(0), cost(0), next(NULL) {}
AdjNode::AdjNode(int v, int weight) : 
    to(v), weight(weight), capacity(0), cost(0), next(NULL) {}
AdjNode::AdjNode(int v, int weight, int capacity) : 
    to(v), weight(weight), capacity(capacity), cost(0), next(NULL) {}
AdjNode::AdjNode(int v, int weight, int capacity, int cost) : 
    to(v), weight(weight), capacity(capacity), cost(cost), next(NULL) {}
AdjNode::AdjNode(int v, AdjNode *next) : 
    to(v), weight(1), capacity(0), cost(0), next(next) {}
AdjNode::AdjNode(int v, int weight, AdjNode *next) : 
    to(v), weight(weight), capacity(0), cost(0), next(next) {}
AdjNode::AdjNode(int v, int weight, int capacity, AdjNode *next) : 
    to(v), weight(weight), capacity(capacity), cost(0), next(next) {}
AdjNode::AdjNode(int v, int weight, int capacity, int cost, AdjNode *next) : 
    to(v), weight(weight), capacity(capacity), cost(cost), next(next) {}

// memeber functions of Edge
Edge::Edge(int from, int to) : from(from), to(to), weight(1), capacity(0), cost(0) {}
Edge::Edge(int from, int to, int weight) : from(from), to(to), weight(weight), capacity(0), cost(0) {}
Edge::Edge(int from, int to, int weight, int capacity) : from(from), to(to), weight(weight), capacity(capacity), cost(0) {}
Edge::Edge(int from, int to, int weight, int capacity, int cost) : from(from), to(to), weight(weight), capacity(capacity), cost(cost) {}

// member functions of Graph
Graph::Graph(int num_vertices, int num_edges, std::pair<int, int> edges[]) : 
    num_vertices(num_vertices), num_edges(num_edges) {
        this->adjlists = new AdjNode *[num_vertices];
        std::memset(this->adjlists, 0, sizeof(AdjNode *) * num_vertices);
        for(int i = 0; i < num_edges; i++) {
            int from = edges[i].first;
            int to = edges[i].second;
            AdjNode *adjnode = new AdjNode(to, this->adjlists[from]);
            this->adjlists[from] = adjnode;
        }
    }

Graph::Graph(int num_vertices, int num_edges, Edge edges[]) : 
    num_vertices(num_vertices), num_edges(num_edges) {
        this->adjlists = new AdjNode *[num_vertices];
        std::memset(this->adjlists, 0, sizeof(AdjNode *) * num_vertices);
        for(int i = 0; i < num_edges; i++) {
            int from = edges[i].from;
            int to = edges[i].to;
            AdjNode *adjnode = new AdjNode(to, edges[i].weight, edges[i].capacity, edges[i].cost, this->adjlists[from]);
            this->adjlists[from] = adjnode;
        }
    }

Graph::~Graph() {
    for(int i = 0; i < this->num_vertices; i++) {
        AdjNode *adjlist = this->adjlists[i];
        while(adjlist != NULL) {
            AdjNode *next = adjlist->next;
            delete adjlist;
            adjlist = next;
        }
    }
    delete this->adjlists;
}

// member functions of UndirectedEdge
UndirectedEdge::UndirectedEdge(int v1, int v2) : v1(v1), v2(v2), weight(1.0) {}
UndirectedEdge::UndirectedEdge(int v1, int v2, double weight) : v1(v1), v2(v2), weight(weight) {}

// member functions of UndirectedEdgedGraph
UndirectedEdgedGraph::UndirectedEdgedGraph(size_t num_vertices, 
        size_t num_edges, UndirectedEdge *edges) : 
    num_vertices(num_vertices), num_edges(num_edges), edges(edges) {}

UndirectedEdgedGraph::~UndirectedEdgedGraph() {
    delete edges;
}
