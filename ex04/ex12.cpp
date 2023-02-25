#include <vector>
#include <iostream>
using namespace std;

class Graph
{
  enum state {UNVISITED, VISITED, FINISHED};

  public:
  Graph(int V):vertices(V) {adjacent = new vector<int>[V];}
  ~Graph(){delete [] adjacent;}
  void addEdge (int u, int v) {adjacent[u].push_back(v);}
  bool cycle (vector<int> &path) const;

  private:
  void dfs (bool &foundCycle, int head, vector<state> &status, vector<int> &prev, vector<int> &path)const;
  int vertices;
  vector<int> * adjacent;
};


bool Graph::cycle(vector<int> &path) const
{
  bool foundCycle = false;
  vector<int> prev(vertices);
  vector<state> status(vertices);
  for (int i = 0; i < vertices; i++)
  {
    status[i] = UNVISITED;
    prev[i] = -1;
  }

  for (int v = 0; v < vertices; v++)
    if (status[v] == UNVISITED)
      dfs(foundCycle, v, status, prev, path);
  return foundCycle;
}


void Graph::dfs (bool &foundCycle, int head, vector<state> &status, vector<int> &prev, vector<int> &path)const
{
  status[head] = VISITED;
  for(int v: adjacent[head])
    if (status[v] == UNVISITED)
    {
      prev[v] = head;
      dfs(foundCycle, v, status, prev, path);
    }
    else if (status[v] == VISITED and foundCycle == false)
    {
      foundCycle = true;
      int curr = head;
      while (curr != v)
      {
        path.insert(path.begin(), curr);
        curr = prev[curr];
      }
      path.insert(path.begin(), curr);
    }
  status[head] = FINISHED;
}
