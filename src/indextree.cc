#include "indextree.hpp"
using namespace std;


IndexTree::IndexTree()
{
  this->vLogSum = vector<double>(2, 0);
}


IndexTree::IndexTree(vector<Document> &vDoc, int variableIndex)
{
  this->Initialize(vDoc, variableIndex);
}


void IndexTree::Initialize(vector<Document> &vDoc, int variableIndex)
{
  this->vDocuments.clear();
  this->nijk.clear();
  this->rootIndex = variableIndex;
  this->depth=0;
  
  
  // Initializing the vDocuments vector
  this->vDocuments.resize(1);
  this->nijk.resize(1);
  for(vector<Document>::iterator it = vDoc.begin(); it != vDoc.end(); it++)
  {
    // If this document doesnt have the {variableIndex} feature, just ignore it
    if(not it->IsSetted(variableIndex)) continue;
    
    int featureValue = it->GetFeature(variableIndex);
    this->nijk[0][featureValue]++;
    this->vDocuments[0].push_back(&(*it));
  }
  
  this->nRootFeatures = this->nijk[0].size();
}


void IndexTree::AddParent(int index)
{
  int sz_vDocuments=0;
  map<int, int> featureToIndex;
  vector<vector<Document*> > neuevDocuments;
  vector<unordered_map<int, int> > neueNijk;
  this->depth++;
  
  
  for(vector<vector<Document*> >::iterator it = this->vDocuments.begin();
      it != this->vDocuments.end(); it++)
  {
    for(vector<Document*>::iterator jt = it->begin(); jt != it->end(); jt++)
    {
      // Ignoring this document in case it doenst have the {index} feature.
      if(not (*jt)->IsSetted(index)) continue;
      
      int featureValue = (*jt)->GetFeature(index);
      int rootFeatureValue = (*jt)->GetFeature(this->rootIndex);
      if(featureToIndex.find(featureValue) == featureToIndex.end())
      {
        featureToIndex[featureValue] = sz_vDocuments++;
        neuevDocuments.push_back(vector<Document*>(1, *jt));
        neueNijk.push_back(unordered_map<int, int>());
        (*neueNijk.rbegin())[rootFeatureValue]=1;
      }
      else
      {
        neuevDocuments[featureToIndex[featureValue]].push_back(*jt);
        neueNijk[featureToIndex[featureValue]][rootFeatureValue]++;
      }
    }
    
    featureToIndex.clear();
  }
  this->vDocuments.clear(); this->nijk.clear();
  this->vDocuments = neuevDocuments;
  this->nijk = neueNijk;
}


double IndexTree::CalcProb()
{
  double lhs=0, rhs=0, div=0;

  for(int i = 0; i < this->nijk.size(); i++)
    for(unordered_map<int, int>::iterator it = this->nijk[i].begin(); it != this->nijk[i].end(); it++)
      rhs += this->CalcSum(it->second);
  
  for(int i = 0; i < this->vDocuments.size(); i++)
    div += this->CalcSum(this->nRootFeatures+this->vDocuments[i].size()-1);
  
  lhs = this->vDocuments.size()*this->CalcSum(this->nRootFeatures-1);
  return lhs+rhs-div;
}


int IndexTree::GetDepth() const
{
  return this->depth;
}

int IndexTree::GetNumberRootFeatures() const
{
  return this->nRootFeatures;
}


/* Basically calculates \sum_{i}^{end} log(i) */
inline double IndexTree::CalcSum(int end)
{
  if(end < 1) return 0;
  if(end < this->vLogSum.size()) return this->vLogSum[end];
  double resp = *this->vLogSum.rbegin();
  for(int i = this->vLogSum.size(); i <= end; i++)
  {
    resp += log(i);
    this->vLogSum.push_back(resp);
  }
  return resp;
}

