#include "database.hpp"
using namespace std;

Database::Database(int nBins)
{ this->_nBins = nBins; }

Database::Database(int nBins, vector<Document> vDocuments) : Database(nBins)
{
  this->_vDocuments = vDocuments;
}

void Database::addDocument(Document *d)
{ this->_vDocuments.push_back(*d); }

void Database::setvDocuments(vector<Document> vDocuments)
{ this->_vDocuments = vDocuments; }

void Database::clearvDocuments()
{ this->_vDocuments.clear(); }

/* Pre Process every kind of feature data used by calcProb */
void Database::preProcessFeatures()
{
  this->_uniqueFeatures.clear();
  this->_uniqueFeatures.resize(this->_nBins);
  for (unsigned int i = 0; i < this->_vDocuments.size(); i++)
    for(int j = 0; j < this->_nBins; j++)
      this->_uniqueFeatures[j].insert(this->_vDocuments[i].getFeature(j));
  
  /* Refreshing _countFeatures */
  this->_countFeatures.assign(this->_uniqueFeatures.size(), 0);
  for(unsigned int i = 0; i < this->_uniqueFeatures.size(); i++)
    this->_countFeatures[i] = this->_uniqueFeatures[i].size();
}

/*
 *  This function returns the number of documents that has
 *  feature[node1]=value 1 and feature[node2]=value2
 */
int Database::countOcurrences(int node1, int value1, int node2, int value2)
{
    int cont=0;
    for(vector<Document>::iterator it = this->_vDocuments.begin(); it != this->_vDocuments.end(); it++)
      if(it->getFeature(node1)==value1 && it->getFeature(node2)==value2) cont++;
    return cont;
}

int Database::countOcurrences(int node, int value, map<int, int> parents)
{
  int c=0; // Counter
  for (unsigned int i = 0; i < this->_vDocuments.size(); i++)
  {
    if(this->_vDocuments[i].getFeature(node)!=value) continue;
    
    bool agree=true;
    for(map<int, int>::iterator it = parents.begin(); it != parents.end(); it++)
      if(this->_vDocuments[i].getFeature(it->first)!=it->second)
      {
        agree=false;
        break;
      }
    if(agree) c++;
  }
  return c;
}

/* Basically calculates \sum_{begin}^{end} */
ll Database::calcSum(int begin, int end)
{
  if(end < begin) return 0;
  return (begin+end)*(end-begin+1)/2;
}

/* Returns the log of the probability function, for precision issues. */
ll Database::calcProb(int node, parents vp)
{
  ll resp=0;
  
  if(this->_uniqueFeatures.size()==0) this->preProcessFeatures();
  
  for(unsigned int i = 0; i < this->_vDocuments.size(); i++)
  {
    ll nij = 0; // Just following the paper's names.
    ll lhsp=0, rhs=0; // Left Hand Side and Right Hand Side of the Productory
    ll div=0; // (Nij + ri - 1)
    
    map<int, int> parentsValues;
    int parentsFeature = this->_vDocuments[i].getFeature(node);
    for(auto it = vp.myParents.begin(); it != vp.myParents.end(); it++)
      parentsValues[*it] = parentsFeature;
    
    //Calculating the Left Hand Side of the productory
    for(set<int>::iterator nIt = this->_uniqueFeatures[node].begin(); nIt != this->_uniqueFeatures[node].end(); nIt++) // Foreach possible value of the node...
    {  
      int ocurrences = countOcurrences(node, *nIt, parentsValues);
      nij += ocurrences;
      rhs += calcSum(0, ocurrences);
      if(node==0) cout << "Node 0 - NIJK = " << ocurrences << endl;
    }
    lhsp = calcSum(0, this->_countFeatures[node]-1);
    div = calcSum(0, nij+this->_countFeatures[node]-1); 
    
    if(node==0)
    cout << "Node = " << node << " (LHSP = " << lhsp << ") + (RHSP = " << rhs << ") - (DIV = " << div << ") TOTAL="
         << lhsp+rhs-div << " NIJ = " << nij << endl;
    // Refreshing resp...
    resp += lhsp+rhs-div;
  }
  cout << "TOTAL = " << resp << endl;
  return resp;
}

/* Returns the log of the probability function, for precision issues. */
ll Database::calcProb(int node, parents vp, int extraParent)
{
  vp.myParents.insert(extraParent);
  return calcProb(node, vp);
}

/* Returns a random feature of the [index] position. */
int Database::getRandomFeature(int index)
{
  vector<int> selectedDocuments;
  
  for(int i = 0; i < this->_vDocuments.size(); i++)
    if(this->_vDocuments[i].isSetted(index))
        selectedDocuments.push_back(i);
  srand(time(NULL));

  if(selectedDocuments.size()==0) return INF;
  int randomIndex = rand()%selectedDocuments.size();
  randomIndex = selectedDocuments[randomIndex];
  
  return this->_vDocuments[randomIndex].getFeature(index);
}

int Database::getRandomFeature(Document base, int index)
{
  /* TODO: After implementing the index tree, better this method using it. */
  
  vector<int> selectedDocuments;
  for(int i = 0; i < this->_vDocuments.size(); i++)
    if(this->_vDocuments[i].hasSameSettedFeatures(base)
       && this->_vDocuments[i].isSetted(index))
        selectedDocuments.push_back(i);
  srand(time(NULL));

  if(selectedDocuments.size()==0)
    return base.getFeature(index);
  
  int randomIndex = rand()%selectedDocuments.size();
  randomIndex = selectedDocuments[randomIndex];
  return this->_vDocuments[randomIndex].getFeature(index);
}

/* It generates a new point, based on the network */
vector<int> Database::generateNewPoint(vector<parents> vp)
{
  int current; // Current Node on the BFS
  queue<int> q;
  vector<bool> visited(vp.size(), false);
  vector<int> ret(vp.size());
  
  
  /* Initializing the queue with nodes that doesn't have a parent. */
  for(int i = 0; i < vp.size(); i++)
    if(vp[i].myParents.size() == 0) q.push(vp[i].node);
  
  while(!q.empty())
  {
    current = q.front();
    q.pop();
    if(visited[current]) continue;
    
    if(vp[current].myParents.size()==0)
      ret[current] = this->getRandomFeature(current);
    else
    {
      Document base(vp.size(), 0);
      
      for(auto it = vp[current].myParents.begin(); it != vp[current].myParents.end(); it++)
        base.setFeature(*it, ret[*it]);
      
      ret[current] = this->getRandomFeature(base, current);
    }
    
    visited[current]=true;
    for(int i = 0; i < vp[current].parentsOf.size(); i++)
      q.push(vp[current].parentsOf[i]);
  }

  return ret;
}
