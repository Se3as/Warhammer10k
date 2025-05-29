#include "DFS.h"

/// Constructor for the DFS class.
DFS::DFS(const Graph& graph) : graph(graph) {}

/// Discovers neighbors of a given node and adds them to the pending set.
void DFS::discoverNeighbors(int node) {
  for (int neighbor : this->graph.getAdjacents(node)) {
    if (this->visitedGlobal.find(neighbor) == this->visitedGlobal.end()) {
      this->pending.insert(neighbor);
    }
  }
}

/// Executes the DFS algorithm starting from a given node.
std::vector<int> DFS::executeDFS(int startNode, int limit) {
  std::vector<int> currentBatch;

  // If the start node has not been visited, add it to the batch
  if (this->visitedGlobal.find(startNode) == this->visitedGlobal.end()) {
    currentBatch.push_back(startNode);
    this->visitedGlobal.insert(startNode);
    this->discoverNeighbors(startNode);
  }

  // Visit up to 'limit' pending nodes
  // +1 for the initial node
  int currentBatchSize = currentBatch.size();
  while (!this->pending.empty() && currentBatchSize < limit + 1) { 
    int node = *this->pending.begin();
    this->pending.erase(this->pending.begin());

    if (this->visitedGlobal.find(node) == this->visitedGlobal.end()) {
      currentBatch.push_back(node);
      this->visitedGlobal.insert(node);
      this->discoverNeighbors(node);
    }

    currentBatchSize = currentBatch.size();
  }

  return currentBatch;
}

/// Checks if all nodes in the graph have been visited.
bool DFS::allVisited() const {
  int visitedCount = this->visitedGlobal.size();
  return visitedCount == this->graph.getNumberOfVertices();
}

/// Resets the DFS state, clearing visited and pending nodes.
void DFS::reset() {
  this->visitedGlobal.clear();
  this->pending.clear();
}

/// Gets the set of globally visited nodes.
const std::unordered_set<int>& DFS::getVisited() const {
  return this->visitedGlobal;
}