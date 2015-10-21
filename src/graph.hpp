#ifndef _graph_hpp
#define _graph_hpp

#include "util.hpp"

template<class T>
class Graph
{
    private:
        int _nNodes;
        std::vector<std::vector<std::pair<int, T> > > _graph;
        std::vector<std::vector<std::pair<int, T> > > _reverseGraph;
        
    public:
        Graph(){}
        Graph(int nNodes);
        
        void clear();
        void addEdge(int from, int to, T weight);
        T getEdgeWeight(int from, int to);
        int getnNodes();
        std::vector<int> pred(int node);
};

#include "graph.cc"

#endif
