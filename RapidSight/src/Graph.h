#pragma once

#include <iostream>
#include <vector>

class Graph {
private:
    std::vector<std::vector<int>> adjacencyList;

public:
    Graph(int numNodes = 0);
    void addEdge(int nodeA, int nodeB);
    const std::vector<int>& getNeighbors(int node) const;
    size_t getNodeCount() const;
};
