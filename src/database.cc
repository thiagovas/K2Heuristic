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
  ll cont=0;
  for(int i = begin; i <= end; i++)
    cont+=i;
  return cont;
}

/* Returns the log of the probability function, for precision issues. */
ll Database::calcProb(int node, parents vp)
{
    ll resp=0;
    
    if(this->_uniqueFeatures.size()==0) this->preProcessFeatures();
    
    for(unsigned int i = 0; i < this->_vDocuments.size(); i++)
    {
        int nij = 0; // Just following the paper's names.
        ll lhsp=0, rhs=0; // Left Hand Side and Right Hand Side of the Productory
        ll div=0; // (Nij + ri - 1)
        
        //Calculating the Left Hand Side of the productory
        for(set<int>::iterator nIt = this->_uniqueFeatures[node].begin(); nIt != this->_uniqueFeatures[node].end(); nIt++) // Foreach possible value of the node...
        {
            map<int, int> parentsValues;
            for(auto it = vp.p.begin(); it != vp.p.end(); it++)
                parentsValues[*it] = this->_vDocuments[i].getFeature(*it);
            int ocurrences = countOcurrences(node, *nIt, parentsValues);
            nij += ocurrences;
            rhs += calcSum(0, ocurrences);
        }
        lhsp = calcSum(0, this->_countFeatures[node]-1);
        div = calcSum(0, nij+this->_countFeatures[node]-1); 
        
        // Refreshing resp...
        resp += lhsp+rhs-div;
    }
    return resp;
}

/* Returns the log of the probability function, for precision issues. */
ll Database::calcProb(int node, parents vp, int extraParent)
{
    vp.p.insert(extraParent);
    return calcProb(node, vp);
}
