#include "Graph.h"

/// Constructor for the Graph class. 
Graph::Graph(int numVertices) : numVertices(numVertices), adj(numVertices) {}

/// Adds an edge between two vertices in the graph.
void Graph::addEdge(int startVertex, int endVertex) {
  this->adj[startVertex].push_back(endVertex);
  this->adj[endVertex].push_back(startVertex);  // Undirected graph
}

/// Gets the adjacent vertices of a given vertex.
const std::vector<int>& Graph::getAdjacents(int node) const {
  return this->adj[node];
}

/// Gets the number of vertices in the graph.
int Graph::getNumberOfVertices() const {
  return this->numVertices;
}

/// Prints the structure of the graph.
void Graph::printGraph() const {
  for (int i = 0; i < this->numVertices; ++i) {
    std::cout << "Node " << i << " -> ";
    for (int neighbor : this->adj[i]) {
      std::cout << neighbor << " ";
    }
    std::cout << std::endl;
  }
}
