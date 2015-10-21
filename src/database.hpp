#ifndef _database_hpp
#define _database_hpp

#include "util.hpp"
#include "document.hpp"

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
        std::vector<Document> _vDocuments;
        std::vector<int> _countFeatures; // Each position keeps the number of different feature
        std::vector<std::set<int> > _uniqueFeatures; // Each set keeps all possible feature
        bool _featuresPreProcessed;
        int _nBins;
        
    public:
        
        Database(int nBins);
        
        Database(int nBins, std::vector<Document> vDocuments);

        double calcProb(int node, parents vp);
        
        double calcProb(int node, parents vp, int extraParent);
        
        //void loadDatabase(); // constructor?
        
        void addDocument(Document *d);
        
        void setvDocuments(std::vector<Document> vDocuments);
        
        void clearvDocuments();
        
        /* Pre Process every kind of feature data used by calcProb */
        void preProcessFeatures();        
};


#endif
