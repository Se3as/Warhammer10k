#include "Graph.h"

Graph::Graph(int numVertices) : numVertices(numVertices), adj(numVertices) {}

void Graph::addEdge(int startVertex, int endVertex) {
  this->adj[startVertex].push_back(endVertex);
  this->adj[endVertex].push_back(startVertex);  // Undirected graph
}

const std::vector<int>& Graph::getAdjacents(int node) const {
  return this->adj[node];
}

int Graph::getNumberOfVertices() const {
    return this->numVertices;
}

void Graph::printGraph() const {
  for (int i = 0; i < this->numVertices; ++i) {
    std::cout << "Node " << i << " -> ";
    for (int neighbor : this->adj[i]) {
      std::cout << neighbor << " ";
    }
    std::cout << std::endl;
  }
}
