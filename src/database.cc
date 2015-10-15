#include "database.hpp"

double Database::calcProb(int node, parents vp)
{
    return 0;
}

double Database::calcProb(int node, parents vp, int extraParent)
{
    vp.p.insert(extraParent);
    return calcProb(node, vp);
}
