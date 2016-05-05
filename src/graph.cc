#ifndef _graph_cc
#define _graph_cc

#include "graph.hpp"
using namespace std;

template<class T>
Graph<T>::Graph(int nNodes)
{
  this->Init(nNodes);
}

template<class T>
void Graph<T>::Clear()
{
  this->_nNodes=0;
  this->_graph.clear();
  this->_reverseGraph.clear();
}

template<class T>
void Graph<T>::Init(int nNodes)
{
  this->Clear();
  this->_nNodes=nNodes;
  this->_graph.resize(nNodes);
  this->_reverseGraph.resize(nNodes);
}

template<class T>
void Graph<T>::AddEdge(int from, int to, T weight)
{
  //TODO: Check (maybe here, maybe somewhere else) if adding this edge we'll have a cycle on the graph.
  //Probably, we can create a method called checkCycle (or something like that), then we'll have to call this method
  //whenever we run K2.
  this->_graph[from].push_back(make_pair(to, weight));
  this->_reverseGraph[to].push_back(make_pair(from, weight));
}

template<class T>
T Graph<T>::GetEdgeWeight(int from, int to) const
{
  for(int i=0; i < this->_graph[from].size(); i++)
    if(this->_graph[from][i].first==to)
      return this->_graph[from][i].second;
  return INF;
}

template<class T>
int Graph<T>::GetnNodes() const
{
  return this->_nNodes;
}

template<class T>
vector<int> Graph<T>::Pred(int node) const
{
  // Run checkCycle()???
  queue<int> q;
  vector<int> visited(this->GetnNodes());
  vector<int> ret;
  int atual;
  
  q.push(node);
  while(!q.empty())
  {
    atual = q.front(); q.pop();
    if(visited[atual]) continue;
    visited[atual]=true;
    if(atual != node) ret.push_back(atual);
    for(int i = 0; i < this->_reverseGraph[atual].size(); i++)
      q.push(this->_reverseGraph[atual][i].first);
  }
  
  return ret;
}

#endif
