#include "Graph.h"

Graph::Graph(int numNodes) : adjacencyList(numNodes) {}

void Graph::addEdge(int nodeA, int nodeB) {
    this->adjacencyList[nodeA].push_back(nodeB);
    this->adjacencyList[nodeB].push_back(nodeA); // Undirected graph
}

const std::vector<int>& Graph::getNeighbors(int node) const {
    return this->adjacencyList[node];
}

size_t Graph::getNodeCount() const {
    return this->adjacencyList.size();
}
