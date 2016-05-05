#include "database.hpp"
using namespace std;

Database::Database(vector<Document> &vDocuments)
{
  this->_vDocuments = vDocuments;
}

void Database::AddDocument(Document *d)
{ this->_vDocuments.push_back(*d); }

void Database::SetvDocuments(vector<Document> vDocuments)
{ this->_vDocuments = vDocuments; }

void Database::ClearvDocuments()
{ this->_vDocuments.clear(); }

/* Returns the log of the probability function, for precision issues. */
double Database::CalcProb(int node, parents &vp, int extraParent)
{
  IndexTree tree;
  tree.Initialize(this->_vDocuments, node);
  
  for(auto it = vp.myParents.begin(); it != vp.myParents.end(); it++)
    tree.AddParent(*it);
  
  if(extraParent != -1)
    tree.AddParent(extraParent);
  
  return tree.CalcProb();
}

/* Returns a random feature of the [index] position. */
int Database::GetRandomFeature(int index) const
{
  vector<int> selectedDocuments;
  
  for(int i = 0; i < this->_vDocuments.size(); i++)
    if(this->_vDocuments[i].IsSetted(index))
        selectedDocuments.push_back(i);
  srand(time(NULL));
  
  if(selectedDocuments.size()==0) return INF;
  int randomIndex = rand()%selectedDocuments.size();
  randomIndex = selectedDocuments[randomIndex];
  
  return this->_vDocuments[randomIndex].GetFeature(index);
}

int Database::GetRandomFeature(Document base, int index) const
{
  /* TODO: After implementing the index tree, better this method using it. */
  
  vector<int> selectedDocuments;
  for(int i = 0; i < this->_vDocuments.size(); i++)
    if(this->_vDocuments[i].HasSameSettedFeatures(base)
       && this->_vDocuments[i].IsSetted(index))
        selectedDocuments.push_back(i);
  srand(time(NULL));
  
  if(selectedDocuments.size()==0)
    return base.GetFeature(index);
  
  int randomIndex = rand()%selectedDocuments.size();
  randomIndex = selectedDocuments[randomIndex];
  return this->_vDocuments[randomIndex].GetFeature(index);
}

/* It generates a new point, based on the network */
vector<int> Database::GenerateNewPoint(vector<parents> &vp) const
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
      ret[current] = this->GetRandomFeature(current);
    else
    {
      Document base(vp.size(), 0);
      
      for(auto it = vp[current].myParents.begin(); it != vp[current].myParents.end(); it++)
        base.SetFeature(*it, ret[*it]);
      
      ret[current] = this->GetRandomFeature(base, current);
    }
    
    visited[current]=true;
    for(int i = 0; i < vp[current].parentsOf.size(); i++)
      q.push(vp[current].parentsOf[i]);
  }

  return ret;
}
