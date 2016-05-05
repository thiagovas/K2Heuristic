#ifndef _database_hpp
#define _database_hpp

#include "util.hpp"
#include "document.hpp"
#include "indextree.hpp"

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
  public:
    
    Database(std::vector<Document> &vDocuments);
    
    /* Returns the log of the probability function, for precision issues. */
    double CalcProb(int node, parents &vp, int extraParent=-1);
    
    void AddDocument(Document *d);
    
    void SetvDocuments(std::vector<Document> vDocuments);
    
    void ClearvDocuments();
    
    std::vector<int> GenerateNewPoint(std::vector<parents> &vp) const;
    
    /* Returns a random feature of the [index] position.
       The feature will be randomly selected among the documents
       that has the same features as the [base] document.
       Only the setted features will be considered.
       */
    int GetRandomFeature(Document base, int index) const;
    
    /* Returns a random feature of the [index] position. */
    int GetRandomFeature(int index) const;

  private:
    std::vector<Document> _vDocuments;
};

#endif
