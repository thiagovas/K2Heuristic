#ifndef _graph_hpp
#define _graph_hpp

#include "util.hpp"
using namespace std;

template<class T>
class Graph
{
    private:
        int _nNodes;
        std::vector<std::vector<std::pair<int, T> > > _graph;
        
    public:
        Graph(){}
        Graph(int nNodes);
        
        void clear();
        void addEdge(int from, int to, T weight);
        T getEdgeWeight(int from, int to);
        int getnNodes();
        std::vector<int> pred(int node);
};


template<class T>
Graph<T>::Graph(int nNodes)
{
    this->_nNodes = nNodes;
}

template<class T>
void Graph<T>::clear()
{
    this->_nNodes=0;
    this->_graph.clear();
}

template<class T>
void Graph<T>::addEdge(int from, int to, T weight)
{
    this->graph[from].push_back(make_pair(to, weight));
}

template<class T>
T Graph<T>::getEdgeWeight(int from, int to)
{
    for(int i=0; i < this->_graph[from].size(); i++)
        if(this->_graph[from][i].first==to)
            return this->_graph[from][i].second;
    return INF;
}

template<class T>
int Graph<T>::getnNodes()
{
    return this->_nNodes;
}

template<class T>
vector<int> Graph<T>::pred(int node)
{
    //TODO: Implement this method;
    return vector<int>();
}

#endif
