#include "graph.hpp"

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
