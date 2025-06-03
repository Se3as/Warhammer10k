#pragma once

#include <iostream>
#include <queue>
#include <set>
#include "Graph.h"

/// Class representing a breadth-first search (BFS) algorithm on a graph only
/// searching neighbors nodes every call
class BFS {
private:
    const Graph& graph;
    std::queue<int> queue;
    std::set<int> visited;
    int currentNode;
    bool firstCall = true;
    std::vector<int> lastLayer;

public:
    BFS(const Graph& g);
    void executeBFS(int initialNode);
    std::vector<int> getCloseNeighbors();
    void reset();

};
