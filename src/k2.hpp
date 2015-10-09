#ifndef _k2_hpp
#define _k2_hpp

#include "util.hpp"
#include "graph.hpp"

typedef struct sParents {
    int node;
    std::set<int> p;

    sParents(int pNode)
    { node=pNode; }
    
    sParents(int pNode, std::set<int> np)
    {
        p=np; //HUE
        node=pNode;
    }
} parents;

class K2
{
    private:
        Graph<int> *_graph;
        //Database? db
        
    public:
        K2();
        void setGraph(Graph<int> *g);
        std::vector<parents> runK2(int u);
};
#endif
