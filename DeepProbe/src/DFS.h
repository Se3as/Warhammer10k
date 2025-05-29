#pragma once
#include "Graph.h"
#include <vector>
#include <unordered_set>
#include <stack>

class DFS { 
private:
    const Graph& graph;
    std::unordered_set<int> visitedGlobal;
    std::unordered_set<int> pending; // Nodos descubiertos pero no visitados

    void discoverNeighbors(int node);

public:
    DFS(const Graph& g);
    std::vector<int> executeDFS(int startNode, int limit);
    bool allVisited() const;
    void reset();
    const std::unordered_set<int>& getVisited() const;
};