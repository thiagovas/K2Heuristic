#include "k2.hpp"
using namespace std;

K2::K2()
{
    this->_graph = NULL;
    // Set the Database as NULL as well.
}

void K2::setGraph(Graph<int> *pg)
{
    assert(pg!=NULL);
    this->_graph=pg;
}

/*
    This functions, basically, runs the K2 Heuristic.
    The param (int u) here is the upper bound on the number of parents a node may have.
*/
vector<parents> K2::runK2(int u)
{
    vector<parents> result;
    for(int i=0; i < this->_graph->getnNodes(); i++)
    {
        parents pi(i);
        double oldProb = 0; //oldProb = db.calcProb(parents);
        bool okToProceed=true;

        while(okToProceed && pi.p.size() < u)
        {
            vector<int> pred = this->_graph->pred(i);
            int maxProbNode=0;
            double newProb=0, tempProb=0;
            
            // Getting the node that maximizes the g function described at the article.
            for(vector<int>::iterator it = pred.begin(); it != pred.end(); it++)
            {
                if(pi.p.find(*it) != pi.p.end()) continue;
                /*
                    if(tempProb=db.calcProb(pi, *it) > newProb)
                    {
                        newProb = tempProb;
                        maxProbNode = *it;
                    }
                */
            }

            if(newProb > oldProb)
            {
                oldProb=newProb;
                pi.p.insert(maxProbNode);
            }
            else okToProceed=false;
        }
        result.push_back(pi);
    }
    return result;
}
