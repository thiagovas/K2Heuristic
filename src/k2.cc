#include "k2.hpp"
using namespace std;

K2::K2()
{ this->_graph = NULL; }

void K2::setGraph(Graph<int> *pg)
{
  assert(pg!=NULL);
  this->_graph=pg;
}

vector<parents> K2::getParents()
{
  // Return a unique_ptr???
  return this->resultK2;
}

/*
    This functions, basically, runs the K2 Heuristic.
    The param int u is the upper bound on the number of parents a node may have.
*/
void K2::runK2(Database *db, int u)
{
    this->resultK2.clear();
    for(int i = 0; i < this->_graph->getnNodes(); i++)
      this->resultK2.push_back(sParents(i, this->_graph->getnNodes()));
    
    for(int i=0; i < this->_graph->getnNodes(); i++)
    {
        parents *pi = &this->resultK2[i]; // Parents of i
        double oldProb = db->calcProb(i, *pi);
        bool okToProceed=true;
        
        while(okToProceed && pi->myParents.size() < u)
        {
            vector<int> pred = this->_graph->pred(i);
            int maxProbNode=0;
            double newProb=INT_MIN, tempProb=0;
            
            // Getting the node that maximizes the g function described at the article.
            for(vector<int>::iterator it = pred.begin(); it != pred.end(); it++)
            {
                if(pi->myParents.find(*it) != pi->myParents.end()) continue;
                
                if((tempProb=db->calcProb(i, *pi, *it)) > newProb)
                {
                    newProb = tempProb;
                    maxProbNode = *it;
                }
            }
            
            // Adding new parent for the node i.
            if(newProb > oldProb)
            {
                oldProb=newProb;
                pi->myParents.insert(maxProbNode);
                this->resultK2[maxProbNode].parentsOf.push_back(i);
            }
            else okToProceed=false;
        }
    }
}
