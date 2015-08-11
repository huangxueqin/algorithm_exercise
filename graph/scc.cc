#include <iostream>
#include <vector>
#include <stack>

struct Edge {
    int src;
    int dest;
    Edge(int s, int d) : src(s), dest(d) {}
};

struct Graph {
    int vertexTotal;
    int edgeTotal;
    std::vector<std::vector<Edge>> adjLists;
};

void PrintGraph(const Graph &graph) {
    std::cout << graph.vertexTotal << " " << graph.edgeTotal << std::endl;
    for(int i = 0; i < graph.vertexTotal; ++i) {
        for(const Edge &e : graph.adjLists[i])
            std::cout << e.src << "---->" << e.dest << std::endl;
    }
}

Graph CreateReverseGraph(const Graph &graph) {
    Graph reverseGraph;
    reverseGraph.vertexTotal = graph.vertexTotal;
    reverseGraph.edgeTotal = graph.edgeTotal;
    reverseGraph.adjLists = std::vector<std::vector<Edge>>(reverseGraph.vertexTotal, 
            std::vector<Edge>());
    for(int i = 0; i < graph.vertexTotal; i++) {
        for(const Edge &e : graph.adjLists[i]) {
            int src = e.dest;
            int dest = e.src;
            reverseGraph.adjLists[src].push_back(Edge(src, dest));
        }
    }
    return reverseGraph;
}

void DFS_Kosaraju(const Graph &graph, const int s, std::vector<bool> &visited, std::vector<int> &vertices) {
    visited[s] = true;
    for(const Edge &e : graph.adjLists[s]) {
        if(!visited[e.dest]) 
            DFS_Kosaraju(graph, e.dest, visited, vertices);
    }
    vertices.push_back(s);
}

void Kosaraju(const Graph &graph, int groups[]) {
    std::vector<bool> visited(graph.vertexTotal, false);
    std::vector<int> vertices;
    for(int i = 0; i < graph.vertexTotal; ++i) {
        if(!visited[i]) {
            DFS_Kosaraju(graph, i, visited, vertices);
        }
    }
    Graph reverseGraph = CreateReverseGraph(graph);
    int groupCount = 0;
    std::stack<int> vertexStack;
    visited = std::vector<bool>(reverseGraph.vertexTotal, false);
    for(auto it = vertices.rbegin(); it != vertices.rend(); it++) {
        int v = *it;
        if(!visited[v]) {
            vertexStack.push(v);
            while(!vertexStack.empty()) {
                int u = vertexStack.top();
                vertexStack.pop();
                if(!visited[u]) {
                    groups[u] = groupCount;
                    visited[u] = true;
                    for(const Edge &e : reverseGraph.adjLists[u]) {
                        if(!visited[e.dest])
                            vertexStack.push(e.dest);
                    }
                }
            }
            ++groupCount;
        }
    }
}

int main(void) {
    Graph graph;
    int vertexTotal, edgeTotal;
    std::cin >> vertexTotal >> edgeTotal;
    graph.vertexTotal = vertexTotal;
    graph.edgeTotal = edgeTotal;
    graph.adjLists = std::vector<std::vector<Edge>>(graph.vertexTotal, std::vector<Edge>());
    for(int i = 0; i < edgeTotal; ++i) {
        int src, dest;
        std::cin >> src >> dest;
        graph.adjLists[src].push_back(Edge(src, dest));
    }
    
    int *sccGroups = new int[graph.vertexTotal];
    Kosaraju(graph, sccGroups);
    for(int i = 0; i < graph.vertexTotal; ++i) {
        std::cout << i << "----" << sccGroups[i] << std::endl;
    }

    return 0;
}
