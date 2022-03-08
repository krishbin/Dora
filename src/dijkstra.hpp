#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <list>
#include <queue>
#include <stack>

using namespace std;
#define INF 0x3f3f3f3f

class Graph
  {
    int V;

    list< pair<int, int> > *adj;

  public:
    Graph(int V);

    void addEdge(int u, int v, int w);
    queue<int> shortestPath(int s,int dest);

    void getPath(int parent[],int j,queue<int> &path);
};

