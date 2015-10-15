#include "document.hpp"
using namespace std;

// Number of features a document has.
// It's worth to point that the vector features not necessarily has nFeatures elements.
// The vector can have less but not more than nFeatures elements.
Document::Document(int _nFeatures)
{
    this->nFeatures = _nFeatures;
}

void Document::initFeatures(int _nFeatures, int value)
{
    this->features = vector<int>(_nFeatures, value);
}

void Document::initFeatures(vector<int> vFeatures)
{
    this->features = vFeatures;
}
