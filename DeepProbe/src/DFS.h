#pragma once
#include "Graph.h"
#include <vector>
#include <set>
#include <stack>

/**
 * @brief Class for Depth-First Search (DFS) algorithm.
 */
class DFS { 
private:
  /**
   * @brief Reference to the graph to be traversed.
   */
  const Graph& graph;
  /**
   * @brief Set of globally visited nodes.
   */
  std::set<int> visitedGlobal;
  /**
   * @brief Set of pending nodes to be visited.
   */
  std::set<int> pending;
  /**
   * @brief Discovers neighbors of a given node and adds them to the 
   * pending set.
   * @param node The node whose neighbors are to be discovered.
   */
  void discoverNeighbors(int node);

public:
  /**
   * @brief Constructor for the DFS class.
   * @param graph The graph to be traversed.
   */
  DFS(const Graph& graph);
  /**
   * @brief Executes the DFS algorithm starting from a given node.
   * @param startNode The node from which to start the DFS.
   * @param limit The maximum number of nodes to visit in this batch.
   * @return A vector containing the nodes visited in this batch.
   */
  std::vector<int> executeDFS(int startNode, int limit);
  /**
   * @brief Checks if all nodes in the graph have been visited.
   * @return True if all nodes have been visited, false otherwise.
   */
  bool allVisited() const;
  /**
   * @brief Resets the DFS state, clearing visited and pending nodes.
   */
  void reset();
  /**
   * @brief Gets the set of globally visited nodes.
   * @return A reference to the set of visited nodes.
   */
  const std::set<int>& getVisited() const;
};