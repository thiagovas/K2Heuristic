#include "util.hpp"
#include "graph.hpp"
#include "k2.hpp"
#include "database.hpp"
using namespace std;

vector<string> splitstr(string s, string delimiter)
{
     vector<string> result;
     string str = s, token;
     size_t pos=0;
     while((pos=str.find(delimiter)) != std::string::npos)
     {
        token = str.substr(0, pos);
        result.push_back(token);
        str.erase(0, pos+delimiter.length());
     }
     result.push_back(str);
     return result;
}

int countFeatures(vector<vector<string> > input)
{
  set<int> s;
  for(int i = 0; i < input.size(); i++)
    for(int j = 2; j < input[i].size()-1; j++)
      s.insert(stoi(splitstr(input[i][j], ":")[0]));
  return s.size();
}

int main()
{
    //ios::sync_with_stdio(false);  cin.tie(0);  cout.tie(0);
     
    string input;
    Graph<int> *g = new Graph<int>();
    K2 *heuristic = new K2();
    Database *db;
    vector<Document> vd;
    vector<vector<string> > vInput;
    
    while(true)
    {
        getline(std::cin, input);
        if(not cin) break;
        vInput.push_back(splitstr(input, " "));
    }
    
    int nFeatures = countFeatures(vInput);
    for(int i = 0; i < vInput.size(); i++)
    {
      Document d(nFeatures);
      for(int j = 2; j < vInput[i].size()-1; j++)
      {
        vector<string> vAux = splitstr(vInput[i][j], ":");
        d.setFeature(stoi(vAux[0])-1, stoi(vAux[1]));
      }
      vd.push_back(d);
    }
    
    db = new Database(nFeatures, vd);
    g->init(nFeatures);
    for(int i = 0; i < nFeatures; i++)
      for(int j = i+1; j < nFeatures; j++)
        g->addEdge(i, j, 0);
    heuristic->setGraph(g);
    
    heuristic->runK2(db, 5);
    vector<parents> resp = heuristic->getParents();
    
    for(int i = 0; i < resp.size(); i++)
    {
      cout << "Node " << resp[i].node << " (" << resp[i].myParents.size() << ") :";
      for(unordered_set<int>::iterator it = resp[i].myParents.begin(); it != resp[i].myParents.end(); it++)
        cout << " " << *it;
      cout << endl << endl;
    }
    
    /* Printing a random feature */
    vector<int> randomFeatures = db->generateNewPoint(resp);
    for(int i = 0; i < randomFeatures.size(); i++)
      cout << randomFeatures[i] << " ";
    cout << endl;
    
    delete g;
    delete heuristic;
    delete db;

    return 0;
}
