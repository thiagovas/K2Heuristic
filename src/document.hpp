#ifndef _document_hpp
#define _document_hpp

#include "util.hpp"


class Document {
  public:
    // Number of features a document has.
    Document(int _nFeatures, int defaultvalue=0);
    
    void InitFeatures(int _nFeatures, int defaultvalue);
    
    void SetFeature(int index, int value);
    
    int GetFeature(int index) const;
    
    bool IsSetted(int index) const;
    
    bool HasSameSettedFeatures(Document &base) const;
    
  private:
    std::vector<int> features;
    
    /* For each position of the feature vector, setted stores
        true if the feature was setted, or the value on the
        feature array is just the default value. */
    std::vector<bool> setted;
    int nFeatures;
    
    // It checks if the index is inside the [0, this->features.size()) interval.
    inline void AssertIndex(int index) const;
};

#endif
