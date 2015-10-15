#ifndef _database_hpp
#define _database_hpp

#include "util.hpp"

typedef struct sParents {
    int node; // The index of the node
    std::unordered_set<int> p; // Its parents

    // Id do verticee e o numero maximo de pais que ele pode ter
    sParents(int pNode, int nParents)
    {
        p.reserve(nParents);
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
