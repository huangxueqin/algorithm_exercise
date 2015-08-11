#include <iostream>
#include <cstddef>
#include <algorithm>
#include <vector>

struct Edge {
    std::size_t src;
    std::size_t dest;
    double weight;
};

struct Graph {
    std::size_t num_vertices;
    std::size_t num_edges;
    Edge *edges;
    ~Graph();
};
Graph::~Graph() { if(edges != NULL) delete edges; }

struct DisjointSet {
    std::size_t size;
    int *parent;
    int *element;

    DisjointSet(std::size_t n) : size(n) {
        parent = new int[n];
        element = new int[n];
        for(int i = 0; i < n; i++) {
            parent[i] = i;
            element[i] = i;
        }
    }
    ~DisjointSet() {
        if(parent != NULL) delete parent;
        if(element != NULL) delete element;
    }

    int FindParent(int t) {
        int elmt = t;
        if(parent[elmt] != elmt) {
            parent[elmt] = FindParent(parent[elmt]);
        }
        return parent[elmt];
    }

    void Merge(int m, int n) {
        int pm = FindParent(m);
        int pn = FindParent(n);
        if(pm != pn) {
            parent[pn] = pm;
        }
    }

    bool IsSameSet(int m, int n) {
        return FindParent(m) == FindParent(n);
    }
};

std::vector<int> KruskalMst(Graph &graph) {
    std::size_t numEdges = graph.num_edges;
    int *edgeIndices = new int[numEdges];
    for(int i = 0; i < numEdges; i++) edgeIndices[i] = i;
    std::sort(edgeIndices, edgeIndices+numEdges, [&graph](const int &a, const int&b) -> 
            bool { return graph.edges[a].weight < graph.edges[b].weight; });
    DisjointSet disjSet(graph.num_vertices);
    std::vector<int> mstSet;
    mstSet.reserve(graph.num_vertices);
    int i = 0;
    while(i < numEdges && mstSet.size() < graph.num_vertices-1) {
        Edge e = graph.edges[edgeIndices[i]];
        if(!disjSet.IsSameSet(e.src, e.dest)) {
            disjSet.Merge(e.src, e.dest);
            mstSet.push_back(edgeIndices[i]);
        }
        i++;
    }
    return mstSet;
}

int main(void) {
    std::size_t v, e;
    std::cin >> v >> e;
    Graph graph;
    graph.num_vertices = v;
    graph.num_edges = e;
    graph.edges = new Edge[e];
    for(int i = 0; i < e; i++) {
        std::size_t src, dest;
        double weight;
        std::cin >> src >> dest >> weight;
        graph.edges[i].src = src;
        graph.edges[i].dest = dest;
        graph.edges[i].weight = weight;
    }

    std::vector<int> mstEdges = KruskalMst(graph);
    for(int i : mstEdges) {
        Edge e = graph.edges[i];
        std::cout << e.src << "----" << e.dest << " : " << e.weight << std::endl;
    }
    return 0;
}

