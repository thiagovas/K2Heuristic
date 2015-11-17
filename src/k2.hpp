#ifndef _k2_hpp
#define _k2_hpp

#include "util.hpp"
#include "graph.hpp"
#include "database.hpp"

class K2
{
  private:
    Graph<int> *_graph;
    vector<parents> resultK2; // It keeps the list of parents that k2 generates
    
  public:
    K2();
    void setGraph(Graph<int> *g);
    void runK2(Database *db, int u);
    vector<parents> getParents();
    
};

#endif
