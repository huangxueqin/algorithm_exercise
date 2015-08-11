#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
#include <cstddef>

struct Edge {
    int src;
    int dest;
    double weight;
    Edge(int src, int dest, int weight) : src(src), dest(dest), weight(weight) {}
};

struct Graph {
    std::size_t numVertices;
    std::size_t numEdges;
    std::vector<Edge> *adjLists;
};

int FindNextMergeVertex(std::vector<bool> &visited, std::vector<double> &dist) {
    double minDist = std::numeric_limits<double>::max();
    int v = -1;
    for(int i = 0; i < visited.size(); i++) {
        if(!visited[i]) {
            if(dist[i] < minDist) {
                v = i;
                minDist = dist[i];
            }
        }
    }
    return v;
}

std::vector<Edge> prim(Graph &graph) {
    std::vector<bool> visited(graph.numVertices, false);
    std::vector<double> dist(graph.numVertices, std::numeric_limits<double>::max());
    std::vector<int> parent(graph.numVertices, -1);
    dist[0] = 0;
    for(int i = 1; i < graph.numVertices; i++) {
        int v = FindNextMergeVertex(visited, dist);
        visited[v] = true;
        for(Edge e : graph.adjLists[v]) {
            int dest = e.dest;
            double weight = e.weight;
            if(!visited[dest]) {
                if(weight < dist[dest]) {
                    parent[dest] = v;
                    dist[dest] = weight;
                }
            }
        }
    }
    std::vector<Edge> result;
    for(int i = 1; i < graph.numVertices; i++) {
        result.push_back(Edge(parent[i], i, dist[i]));
    }
    return result;
}

int main(void) {
    Graph graph;
    size_t vertexTotal, edgeTotal;
    std::cin >> vertexTotal >> edgeTotal;
    graph.numEdges = edgeTotal;
    graph.numVertices = vertexTotal;
    graph.adjLists = new std::vector<Edge>[vertexTotal];
    for(int i = 0; i < edgeTotal; i++) {
        int src, dest;
        double weight;
        std::cin >> src >> dest >> weight;
        graph.adjLists[src].push_back(Edge(src, dest, weight));
        graph.adjLists[dest].push_back(Edge(dest, src, weight));
    }

    std::vector<Edge> mstEdges = prim(graph);
    for(Edge e : mstEdges) {
        std::cout << e.src << "----" << e.dest << " : " << e.weight << std::endl;
    }
    delete[] graph.adjLists;
    return 0;
}
