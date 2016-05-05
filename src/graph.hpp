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
    
    void Init(int nNodes);
    void Clear();
    void AddEdge(int from, int to, T weight);
    T GetEdgeWeight(int from, int to) const;
    int GetnNodes() const;
    std::vector<int> Pred(int node) const;
};

#include "graph.cc"

#endif
