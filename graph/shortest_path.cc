/**
 * This file summarize Four method to compute shortest path of a graph
 * For single source:
 * 1. Dijkstra
 * 2. Bellman-Ford
 * For whole source:
 * 3. Floyd-Warshall
 * 4. Johnson
 */
#include <iostream>
#include <vector>
#include <list>

using std::vector;
using std::list;
using std::cin;
using std::cout;
using std::endl;

struct Edge {
    int v;
    int weight;
};

/**
 * Dijkstra shortest path algorithm, only use when there is no **negetive** edges
 * @param graph     input graph
 * @param s         source vertex
 * @param dist      path distance of source to each vertex
 * @param parent    parent vertex of each vertex in path
 */

void dijkstra(const vector<list<Edge>> &graph, const int s, vector<int> &dist, vector<int> &parent) {
    int vertexNum = graph.size();
    for(int i = 0; i < vertexNum; i++) {
        dist[i] = -1;
        parent[i] = -1;
    }
    auto comparator = [&dist](const int &lhs, const int &rhs) -> bool { return dist[lhs] < dist[rhs]; };
    dist[s] = 0;

}
