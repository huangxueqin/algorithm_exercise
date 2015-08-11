#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;
const ll MOD = 142857;

void propagate(const vector<vector<int>> &graph, vector<int> &indegrees, 
        vector<int> &virusDistribute, int index, ll &sum) {
    indegrees[index] -= 1;
    sum += virusDistribute[index];
    if(sum > MOD) 
        sum %= MOD;
    for(const int &sub : graph[index]) {
        virusDistribute[sub] += virusDistribute[index];
        if(virusDistribute[sub] > MOD)
            virusDistribute[sub] %= MOD;
        indegrees[sub] -= 1;
        if(indegrees[sub] == 0) {
            propagate(graph, indegrees, virusDistribute, sub, sum);
        }
    }
}

ll GetVirusTotal(const vector<vector<int>> &graph, vector<int> &indegrees, 
        vector<int> &virusDistribute) {
    ll sum = 0;
    for(int i = 0; i < graph.size(); i++) {
        if(indegrees[i] == 0) {
            propagate(graph, indegrees, virusDistribute, i, sum);
        }
    }
    return sum % MOD;
}

int main(void) {
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<int>> graph(N);
    vector<int> virusNums(N, 0);
    vector<int> degrees(N, 0);
    for(int i = 0; i < K; i++) {
        int index;
        cin >> index;
        virusNums[index-1]++;
    }
    for(int i = 0; i < M; i++) {
        int from, to;
        cin >> from >> to;
        graph[from-1].push_back(to-1);
        degrees[to-1]++;
    }
    cout << GetVirusTotal(graph, degrees, virusNums) << endl;
    return 0;
}
