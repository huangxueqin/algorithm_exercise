#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <queue>

int Dfs(const int s, const int t,
        std::vector<std::vector<int>> &rGraph, 
        std::vector<bool> &visited, 
        std::vector<int> &path) {
    visited[s] = true;
    path.push_back(s);
    if(s == t) return INT_MAX;

    int vertexTotal = rGraph.size();
    int flow = 0;
    int i = 0;
    while(i < vertexTotal && flow == 0) {
        if(rGraph[s][i] > 0 && !visited[i]) {
            flow = std::min(Dfs(i, t, rGraph, visited, path), rGraph[s][i]);
        }
        i++;
    }
    if(flow == 0) {
        path.pop_back();
        visited[s] = false;
    }
    return flow;
}

int FordFulkerson_Matrix_DFS(std::vector<std::vector<int>> &graph, const int s, const int t) {
    std::vector<std::vector<int>> &rGraph(graph);
    int rowNum = rGraph.size();
    int maxFlow = 0;
    while(true) {
        std::vector<int> path; path.reserve(rowNum);
        std::vector<bool> visited(rowNum, false);
        int flow = Dfs(s, t, rGraph, visited, path);
        if(flow > 0) {
            maxFlow += flow;
            for(int j = 0; j < path.size()-1; j++) {
                int src = path[j];
                int dest = path[j+1];
                rGraph[src][dest] -= flow;
                rGraph[dest][src] += flow;
            }
        }
        else break;
    }
    return maxFlow;
}

int FordFulkerson_Matrix_BFS(const std::vector<std::vector<int>> &graph, const int s, const int t);
int main(void) {
    int vertexTotal;
    std::cin >> vertexTotal;
    std::vector<std::vector<int>> graph(vertexTotal, std::vector<int>(vertexTotal, 0));
    for(int r = 0; r < vertexTotal; r++) 
        for(int c = 0; c < vertexTotal; c++) 
            std::cin >> graph[r][c];
    int s, t;
    std::cin >> s >> t;
    std::cout << FordFulkerson_Matrix_BFS(graph, s, t) << std::endl;
    std::cout << FordFulkerson_Matrix_DFS(graph, s, t) << std::endl;
    return 0;
}

bool BFS(const int s, const int t, 
         std::vector<std::vector<int>> &rGraph, 
         std::vector<int> &path) {
    std::vector<bool> visited(rGraph.size(), false);
    std::queue<int> vertexQueue;
    vertexQueue.push(s);
    visited[s] = true;
    while(!vertexQueue.empty()) {
        int src = vertexQueue.front();
        vertexQueue.pop();
        for(int dest = 0; dest < rGraph.size(); ++dest) {
            if(!visited[dest] && rGraph[src][dest] > 0) {
                visited[dest] = true;
                vertexQueue.push(dest);
                path[dest] = src;
            }
        }
    }
    return visited[t];
}

int FordFulkerson_Matrix_BFS(const std::vector<std::vector<int>> &graph, const int s, const int t) {
    std::vector<std::vector<int>> rGraph(graph);
    std::vector<int> parent(graph.size(), -1);
    int maxFlow = 0;
    while(BFS(s, t, rGraph, parent)) {
        int dest = t;
        int minFlow = INT_MAX;
        while(parent[dest] >= 0) {
            int src = parent[dest];
            minFlow = std::min(minFlow, rGraph[src][dest]);
            dest = src;
        }
        dest = t;
        while(parent[dest] >= 0) {
            int src = parent[dest];
            rGraph[src][dest] -= minFlow;
            dest = src;
        }
        maxFlow += minFlow;
    }
    return maxFlow;
}
