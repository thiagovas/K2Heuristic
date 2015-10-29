#include "document.hpp"
using namespace std;

// Number of features a document has.
// It's worth to point that the vector features not necessarily has nFeatures elements.
// The vector can have less but not more than nFeatures elements.
Document::Document(int _nFeatures, int defaultvalue)
{
  this->nFeatures = _nFeatures;
  this->initFeatures(_nFeatures, defaultvalue);
}

void Document::initFeatures(int _nFeatures, int defaultvalue)
{
    this->features = vector<int>(_nFeatures, defaultvalue);
}

/* Given an index, this function returns its respective feature */
int Document::getFeature(int index)
{
    assert(this->features.size() > index);
    assert(index >= 0);
    return this->features[index];
}

void Document::setFeature(int index, int value)
{
  this->features[index]=value;
}
