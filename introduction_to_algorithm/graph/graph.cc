#include <string>
#include <sstream>
#include "graph.h"

std::string itoa(int i) {
    std::stringstream ss;
    ss << i;
    return ss.str();
}

Graph::Graph(int numVertices) {
    this->numVertices = numVertices;
    this->numEdges = 0;
    for(int i=0;i<numVertices;i++) {
        this->adjs.push_back(new std::vector<int>());
    }
}

Graph::Graph(std::vector<std::vector<int> > &adjs) {
    this->numVertices = adjs.size();
    this->numEdges = 0;
    for(int i=0;i<this->numVertices;i++) {
        std::vector<int> adj = adjs[i];
        this->numEdges += adj.size();
        std::vector<int> *cAdj = new std::vector<int> (adj);
        this->adjs.push_back(cAdj);
    }
}

void Graph::addEdge(int v, int w) {
    std::vector<int> *adj = adjs[v];
    adj->push_back(w);
}

std::string Graph::toString() {
    std::string str;
    for(int i=0;i<this->numVertices;i++) {
        str += itoa(i);
        str += "->";
        std::vector<int> *adj = this->adjs[i];
        int adjNum = adj->size();
        for(int j=0;j<adjNum;j++) {
            str += itoa((*adj)[j]);
            if(j < adjNum - 1) {
                str += "->";
            }
        }
        if(i < this->numVertices - 1) {
            str += "\n";
        }
    }
    return str;
}

Graph::~Graph() {
    for(int i=0;i<this->numVertices;i++) {
        delete this->adjs[i];
    }
}


