#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <list>
#include <queue>
#include <stack>
#include <glm/glm.hpp>

using namespace std;
#define INF 0x3f3f3f3f

class Graph
  {
    int V;
    list<pair<int, int>> *adj;
    list<pair<int,int>> vertexPair;
    glm::vec3 *vertex;

  public:
    Graph(int V,glm::vec3 *vertexLocation);

    void addEdge(int u, int v, int w);
    queue<int> shortestPath(int s,int dest);

    void drawAllNodes(glm::mat4 &pvm);
    void drawShortestPath(int s,int d,glm::mat4 &pvm);
    void getPath(int parent[],int j,queue<int> &path);
};

