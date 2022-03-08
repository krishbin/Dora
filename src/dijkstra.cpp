#include "dijkstra.hpp"

void Graph::getPath(int parent[], int j, queue<int> &path) {
  if (parent[j] == -1) return;
  getPath(parent, parent[j], path);
  path.push(j);
}

Graph::Graph(int V) {
  this->V = V;
  adj = new list<pair<int, int>>[V];
}

void Graph::addEdge(int u, int v, int w) {
  adj[u].push_back(make_pair(v, w));
  adj[v].push_back(make_pair(u, w));
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
