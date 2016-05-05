#include "util.hpp"
#include "graph.hpp"
#include "k2.hpp"
#include "database.hpp"
using namespace std;

vector<string> Splitstr(string s, string delimiter)
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

bool HasCollon(string &s)
{
  bool has=false;
  for(int k = 0; k < s.size(); k++)
    if(s[k]==':')
    {
      has=true;
      break;
    }
  return has;
}

int CountFeatures(vector<vector<string> > input)
{
  set<int> s;
  for(int i = 0; i < input.size(); i++)
    for(int j = 2; j < input[i].size()-1; j++)
      if(HasCollon(input[i][j]))
      {
        s.insert(stoi(Splitstr(input[i][j], ":")[0]));
      }
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
    vInput.push_back(Splitstr(input, " "));
  }
  
  int nFeatures = CountFeatures(vInput);
  for(int i = 0; i < vInput.size(); i++)
  {
    Document d(nFeatures);
    for(int j = 2; j < vInput[i].size()-1; j++)
    {
      if(!HasCollon(vInput[i][j])) break;
      vector<string> vAux = Splitstr(vInput[i][j], ":");
      float featureValue = stof(vAux[1]);
      d.SetFeature(stoi(vAux[0])-1, (int)round(featureValue));
    }
    vd.push_back(d);
  }
  
  db = new Database(vd);
  g->Init(nFeatures);
  for(int i = 0; i < nFeatures; i++)
    for(int j = i+1; j < nFeatures; j++)
      g->AddEdge(i, j, 0);
  heuristic->SetGraph(g);
  
  heuristic->RunK2(db, 5);
  vector<parents> resp = heuristic->GetParents();
  
  for(int i = 0; i < resp.size(); i++)
  {
    cout << "Node " << resp[i].node << " (" << resp[i].myParents.size() << ") :";
    for(unordered_set<int>::iterator it = resp[i].myParents.begin(); it != resp[i].myParents.end(); it++)
      cout << " " << *it;
    cout << endl << endl;
  }
  
  /* Printing a random feature */
  vector<int> randomFeatures = db->GenerateNewPoint(resp);
  for(int i = 0; i < randomFeatures.size(); i++)
    cout << randomFeatures[i] << " ";
  cout << endl;
  
  delete g;
  delete heuristic;
  delete db;

  return 0;
}
