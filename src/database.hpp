#ifndef _database_hpp
#define _database_hpp

#include "util.hpp"

typedef struct sParents {
    int node; // The index of the node
    std::set<int> p; // Its parents

    sParents(int pNode)
    { node=pNode; }
    
    sParents(int pNode, std::set<int> np)
    {
        p=np; //HUE
        node=pNode;
    }
} parents;

class Database {
    private:
        
        
    public:
       double calcProb(int node, parents vp);
       double calcProb(int node, parents vp, int extraParent);
};


#endif
