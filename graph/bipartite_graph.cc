#include <iostream>
#include <queue>
#include <vector>

void PrintGraph(int **graph, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            std::cout << graph[i][j] << " ";
        std::cout << std::endl;
    }
}

/****************************** Max Flow Methon Solve Maxminum Matching ***************************/
bool BFS_FordFulkerson(int **graph, const int n, const int s, const int t, int *parent) {
    bool *visited = new bool[n];
    for(int i = 0; i < n; i++) visited[i] = false;
    std::queue<int> myQueue;
    myQueue.push(s);
    visited[s] = true;
    while(!myQueue.empty()) {
        int v = myQueue.front(); myQueue.pop();
        for(int j = 0; j < n; j++) {
            if(!visited[j] && graph[v][j] > 0) {
                visited[j] = true;
                parent[j] = v;
                myQueue.push(j);
            }
        }
    }
    bool found = visited[t];
    delete [] visited;
    return found;
}

template <std::size_t num>
int MaximumMatching_FordFulkerson(const int (&graph)[num][num], int numPart1, int numPart2) {
    int n = num+2;
    // build a new graph for applying max flow algorithm
    int **ffGraph = new int *[n];
    for(int i = 0; i < n; ++i) ffGraph[i] = new int[n];
    for(int j = 1; j <= numPart1; ++j) 
        ffGraph[0][j] = 1;
    for(int i = numPart1+1; i <= numPart1+numPart2; ++i)
        ffGraph[i][n-1] = 1;
    for(int i = 0; i < numPart1; ++i) {
        for(int j = numPart1; j < num; ++j) {
            ffGraph[i+1][j+1] = graph[i][j];
        }
    }

    // ford-fulkerson algorithm
    int maxFlow = 0;
    int *parent = new int[n]; for(int i = 0; i < n; i++) parent[i] = -1;
    while(BFS_FordFulkerson(ffGraph, n, 0, n-1, parent)) {
        maxFlow += 1;
        int t = n-1;
        while(parent[t] >= 0) {
            int s = parent[t];
            ffGraph[s][t] -= 1;
            ffGraph[t][s] += 1;
            t = s;
        }
    }

    for(int i = 0; i < n; i++) {
        delete [] ffGraph[i];
    }
    delete [] ffGraph;
    delete [] parent;

    return maxFlow;
}

/****************************** Hungarian Methon Solve Maxminum Matching ***************************/
struct Edge {
    int src;
    int dest;
    bool choosed;
    Edge(int s, int d) : src(s), dest(d), choosed(false) {}
};

struct Graph {
    int vertexTotal;
    std::vector<std::vector<Edge>> adjLists;
};

template <std::size_t num>
Graph BuildGraph(const int (&arr)[num][num], int numPart1) {
    Graph graph;
    graph.vertexTotal = num;
    graph.adjLists = std::vector<std::vector<Edge>>(num, std::vector<Edge>());
    for(int i = 0; i < numPart1; i++) {
        for(int j = numPart1; j < num; j++) {
            if(arr[i][j] > 0) {
                graph.adjLists[i].push_back(Edge(i, j));
                graph.adjLists[j].push_back(Edge(j, i));
            }
        }
    }
    return graph;
}

template <std::size_t num>
bool DFS_Hungrian(const int(&graph)[num][num], const int s, std::vector<bool> &visited, std::vector<int> matched) {
    visited[s] = true;
    for(int i = 0; i < num; i++) {
        if(graph[s][i] > 0 && !visited[i]) {
            visited[i] = true;
            if(matched[i] == -1 || DFS_Hungrian(graph, matched[i], visited, matched)) {
                matched[s] = i;
                matched[i] = s;
                return true;
            }
        }
    }
    return false;
}

template <std::size_t num>
int MaximumMatching_Hungarian_DFS(const int (&graph)[num][num], const int numLeft) {
    int maxMatch = 0;
    std::vector<int> matched(num, -1);
    for(int i = 0; i < numLeft; i++) {
        if(matched[i] == -1) {
            std::vector<bool> visited(num, false);
            if(DFS_Hungrian(graph, i, visited, matched)) {
                maxMatch += 1;
            }
        }
    }
    return maxMatch;
}

void BFS_Hungrian(const Graph &graph, const std::vector<int> &matched, int s, 
        int &t, std::vector<int> &parent) {
    std::vector<bool> visited(graph.vertexTotal, false);
    std::vector<int> distance(graph.vertexTotal, -1);
    std::queue<int> myQueue;
    myQueue.push(s);
    visited[s] = true;
    distance[s] = 0;
    while(!myQueue.empty()) {
        int u = myQueue.front(); myQueue.pop();
        int dist = distance[u];
        if(dist & 0x1) {
            int v = matched[u];
            if(!visited[v]) {
                parent[v] = u;
                visited[v] = true;
                distance[v] = dist+1;
                myQueue.push(v);
            }
        }
        else {
            for(const Edge &e : graph.adjLists[u]) {
                int v = e.dest;
                if(!visited[v]) {
                    parent[v] = u;
                    if(matched[v] == -1) {
                        t = v;
                        return;
                    }
                    else {
                        visited[v] = true;
                        distance[v] = dist+1;
                        myQueue.push(v);
                    }
                }
            }
        }
    }
}

template <std::size_t num>
int MaximumMatching_Hungarian_BFS(const int (&graph)[num][num], const int numPart1) {
    Graph bGraph = BuildGraph(graph, numPart1);
    std::vector<bool> valid(bGraph.vertexTotal, true);
    std::vector<int> matched(bGraph.vertexTotal, -1);
    int maxMatch = 0;
    while(true) {
        int s = -1, t = -1;
        for(int i = 0; i < bGraph.vertexTotal; i++) {
            if(valid[i] && matched[i] == -1) {
                s = i;
                break;
            }
        }
        if(s == -1) {
            break;
        }
        std::vector<int> parent(bGraph.vertexTotal, -1);
        BFS_Hungrian(bGraph, matched, s, t, parent);
        if(t == -1) {
            valid[s] = false;
        }
        else {
            maxMatch += 1;
            while(t >= 0 && parent[t] >= 0) {
                int pt = parent[t];
                matched[t] = pt;
                matched[pt] = t;
                t = parent[pt];
            }
        }
    }
    return maxMatch;
}

int main(void) {
    const int bgraph[8][8] = {
        {0,0,0,0,1,0,1,0},  
        {0,0,0,0,1,0,0,0},  
        {0,0,0,0,1,1,0,0},  
        {0,0,0,0,0,0,1,1},  
        {0,0,0,0,0,0,0,0},  
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}
    };  
    std::cout << MaximumMatching_FordFulkerson(bgraph, 4, 4) << std::endl;
    std::cout << MaximumMatching_Hungarian_BFS(bgraph, 4) << std::endl;
    std::cout << MaximumMatching_Hungarian_DFS(bgraph, 4) << std::endl;
    return 0;
}
