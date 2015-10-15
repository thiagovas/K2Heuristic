#ifndef _k2_hpp
#define _k2_hpp

#include "util.hpp"
#include "graph.hpp"
#include "database.hpp"

class K2
{
    private:
        Graph<int> *_graph;
        
    public:
        K2();
        void setGraph(Graph<int> *g);
        std::vector<parents> runK2(Database *db, int u);
};

#endif
