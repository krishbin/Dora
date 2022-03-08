#include "dijkstra.hpp"
#include "polygons.cpp"

void Graph::drawAllNodes(glm::mat4 &pvm){
  for(list<pair<int,int>>::iterator it = vertexPair.begin(); it != vertexPair.end(); ++it){
    Line line(vertex[(*it).first],vertex[(*it).second]);
    line.draw(pvm);
  }
};

void Graph::drawShortestPath(int s,int d,glm::mat4 &pvm){
  queue<int> path(shortestPath(s,d));
  int first = path.front();
  path.pop();
  while(!path.empty()){
    int second = path.front();
    Line line(vertex[first],vertex[second]);
    line.setColor(vec3(0.8f,0.3f,0.4f));
    line.draw(pvm);
    path.pop();
    first = second;
  }
}

void Graph::getPath(int parent[], int j, queue<int> &path) {
  if (parent[j] == -1) return;
  getPath(parent, parent[j], path);
  path.push(j);
}

Graph::Graph(int V,glm::vec3 *vertexLocation) {
  this->V = V;
  adj = new list<pair<int, int>>[V];
  vertex = new glm::vec3[V];
  for(int i = 0; i < V; ++i){
    vertex[i] = vertexLocation[i];
  }
}

void Graph::addEdge(int u, int v, int w) {
  adj[u].push_back(make_pair(v, w));
  adj[v].push_back(make_pair(u, w));
  vertexPair.push_back(make_pair(u,v));
}

queue<int> Graph::shortestPath(int src, int dest) {
  set<pair<int, int>> processingSet;
  vector<int> dist(V, INF);
  // front to back path.front() and path.pop()
  queue<int> path;

  path.push(src);
  int *parent = new int[V];
  for (int i = 0; i < V; ++i) {
    parent[i] = -1;
  }

  processingSet.insert(make_pair(0, src));
  dist[src] = 0;

  while (!processingSet.empty()) {
    pair<int, int> tmp = *(processingSet.begin());
    processingSet.erase(processingSet.begin());

    int u = tmp.second;

    list<pair<int, int>>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
      int v = (*i).first;
      int weight = (*i).second;

      if (dist[v] > dist[u] + weight) {
        if (dist[v] != INF)
          processingSet.erase(processingSet.find(make_pair(dist[v], v)));
        parent[v] = u;
        dist[v] = dist[u] + weight;
        processingSet.insert(make_pair(dist[v], v));
      }
    }
  }
  getPath(parent, dest, path);
  return path;
}
