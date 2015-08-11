#include <iostream>
#include <vector>
#include <limits>

struct Edge {
    int src;
    int dest;
    double weight;
    Edge(int s, int d, double w) : src(s), dest(d), weight(w) {}
};

struct Graph {
    int vertexTotal;
    int edgeTotal;
    std::vector<Edge> *adjLists;
    ~Graph() { if(adjLists != NULL) delete [] adjLists; }
};

const double INFINITE = std::numeric_limits<double>::max();

bool BellmanFord(const Graph &graph, const int s, double dist[], int pre[]) {
    int vertexTotal = graph.vertexTotal;
    for(int i = 0; i < vertexTotal; i++) {
        dist[i] = INFINITE;
        pre[i] = -1;
    }
    dist[s] = 0;
    for(int i = 1; i < vertexTotal; i++) {
        for(int k = 0; k < vertexTotal; k++) {
            if(dist[k] != INFINITE) {
                for(Edge e : graph.adjLists[k]) {
                    int dest = e.dest;
                    double weight = e.weight;
                    if(dist[k] + weight < dist[dest]) {
                        pre[dest] = k;
                        dist[k] = dist[k] + weight;
                    }
                }
            }
        }
    }
    for(int i = 0; i < vertexTotal; i++) {
        for(Edge e : graph.adjLists[i]) {
            int dest = e.dest;
            double weight = e.weight;
            if(dist[i] + weight < dist[dest])
                return false;
        }
    }
    return true;
}

int main(void) {
    Graph graph;
    size_t vertexTotal, edgeTotal;
    std::cin >> vertexTotal >> edgeTotal;
    graph.edgeTotal = edgeTotal;
    graph.vertexTotal = vertexTotal;
    graph.adjLists = new std::vector<Edge>[vertexTotal];
    for(int i = 0; i < edgeTotal; i++) {
        int src, dest;
        double weight;
        std::cin >> src >> dest >> weight;
        graph.adjLists[src].push_back(Edge(src, dest, weight));
    }
    double *dist = new double[vertexTotal];
    int *pre = new int[vertexTotal];
    BellmanFord(graph, 0, dist, pre);
    for(int i = 0; i < vertexTotal; i++) {
        std::cout << dist[i] << std::endl;
    }
    return 0;
}
