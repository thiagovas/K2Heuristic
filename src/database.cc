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
    //TODO: Implement It
}

double Database::calcProb(int node, parents vp)
{
    //TODO: Implement It
    return 0;
}

double Database::calcProb(int node, parents vp, int extraParent)
{
    vp.p.insert(extraParent);
    return calcProb(node, vp);
}
