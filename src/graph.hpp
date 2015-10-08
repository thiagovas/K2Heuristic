#ifndef _graph_hpp
#define _graph_hpp

#include "util.hpp"
using namespace std;

template<class T>
class Graph
{
    private:
        int _nNodes;
        vector<vector<pair<int, T> > > _graph;
        
    public:
        Graph(){}
        Graph(int nNodes);
        
        void clear();
        void addEdge(int from, int to, T weight);
        T getEdgeWeight(int from, int to);
};

#endif
