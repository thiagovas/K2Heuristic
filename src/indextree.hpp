#ifndef _indextree_hpp
#define _indextree_hpp

#include <vector>
#include <unordered_map>
#include "util.hpp"
#include "document.hpp"

class IndexTree {
  public:
    
    IndexTree();
    
    IndexTree(std::vector<Document> &vDoc, int variableIndex);
    
    void Initialize(std::vector<Document> &vDoc, int variableIndex);
    
    void AddParent(int index);
    
    double CalcProb();
    
    int GetDepth() const;
    
    int GetNumberRootFeatures() const;
    
  private:
    
    // This is the structure used to represent the tree
    // Each vector<Document&> represents a leave of the tree.
    std::vector<std::vector<Document*> > vDocuments;
    
    // This vector keeps the values of nijk for each
    // k of a leave
    std::vector<std::unordered_map<int, int> > nijk;
    
    // This vector is used just to prevent the method
    // CalSum to recalculate 
    std::vector<double> vLogSum;
    
    // This integer keeps the index of the root of the tree
    int rootIndex;
    
    // This variable keeps the depth of the tree
    // The same as the number of parents
    int depth;
    
    // This variable keeps the number of features the root has. 
    int nRootFeatures;
     
    /* Basically calculates \sum_{1}^{end} log(i) */
    inline double CalcSum(int end);
};

#endif
