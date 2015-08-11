#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <string>

class Graph {
private:
    int numVertices;
    int numEdges;
    std::vector<std::vector<int> *> adjs;
public:
    Graph(int numVertices);
    Graph(std::vector<std::vector<int> > &adjs);
    void addEdge(int v, int w);
    std::string toString();
    ~Graph();
};   

#endif
