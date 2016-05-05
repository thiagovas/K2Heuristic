#include "document.hpp"
using namespace std;

// _nFeatures - Number of features a document has.
Document::Document(int _nFeatures, int defaultvalue)
{
  this->nFeatures = _nFeatures;
  this->InitFeatures(_nFeatures, defaultvalue);
}

void Document::InitFeatures(int _nFeatures, int defaultvalue)
{
  this->features = vector<int>(_nFeatures, defaultvalue);
  this->setted = vector<bool>(_nFeatures, false);
}

/* Given an index, this function returns its respective feature */
int Document::GetFeature(int index) const
{
  this->AssertIndex(index);
  return this->features[index];
}

void Document::SetFeature(int index, int value)
{
  this->AssertIndex(index);
  this->setted[index]=true;
  this->features[index]=value;
}

bool Document::IsSetted(int index) const
{
  this->AssertIndex(index);
  return (this->setted[index]==true);
}

bool Document::HasSameSettedFeatures(Document &base) const
{
  bool resp=true;
  int i=0, j=0;
  while(i < this->features.size() && j < base.features.size())
  {
    if(base.setted[j])
    {
      if(not this->setted[i])
      {
        resp=false;
        break;
      }
      else if(this->features[i] != base.features[j])
      {
        resp=false;
        break;
      }
    }
    i++; j++;
  }
  
  while(j < base.features.size())
  {
    if(base.setted[j])
    {
      resp=false;
      break;
    }
  }
  return resp;
}

inline void Document::AssertIndex(int index) const
{
  assert(this->features.size() > index);
  assert(index >= 0);
}
