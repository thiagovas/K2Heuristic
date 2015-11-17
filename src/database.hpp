#ifndef _database_hpp
#define _database_hpp

#include "util.hpp"
#include "document.hpp"

typedef struct sParents {
  int node; // The index of the node
  std::unordered_set<int> myParents; // Its parents
  std::vector<int> parentsOf; // The sons of this node.

  // Id do vertice e e o numero maximo de pais que ele pode ter
  sParents(int pNode, int nParents)
  {
    myParents.reserve(nParents);
    node=pNode;
  }
} parents;

class Database
{
  private:
    std::vector<Document> _vDocuments;
    std::vector<int> _countFeatures; // Each position keeps the number of different features
    std::vector<std::set<int> > _uniqueFeatures; // Each set keeps all possible features
    bool _featuresPreProcessed;
    int _nBins;
    
    ll calcSum(int begin, int end);
    
    /*
     *  This function returns the number of documents that has
     *  feature[node1]=value 1 and feature[node2]=value2
     */
    int countOcurrences(int node1, int value1, int node2, int value2);
    int countOcurrences(int node, int value, std::map<int, int> parents);
    
    
  public:
    
    Database(int nBins);
    
    Database(int nBins, std::vector<Document> vDocuments);
    
    /* Returns the log of the probability function, for precision issues. */
    ll calcProb(int node, parents vp);
    
    /* Returns the log of the probability function, for precision issues. */
    ll calcProb(int node, parents vp, int extraParent);
    
    void addDocument(Document *d);
    
    void setvDocuments(std::vector<Document> vDocuments);
    
    void clearvDocuments();
    
    /* Pre Process every kind of feature data used by calcProb */
    void preProcessFeatures();
    
    /* Pass the vector<parents> as unique_ptr, maybe?? */
    std::vector<int> generateNewPoint(std::vector<parents> vp);
    
    /* Returns a random feature of the [index] position.
       The feature will be randomly selected among the documents
       that has the same features as the [base] document.
       Only the setted features will be considered.
       */
    int getRandomFeature(Document base, int index);
    
    /* Returns a random feature of the [index] position. */
    int getRandomFeature(int index);
};

#endif
