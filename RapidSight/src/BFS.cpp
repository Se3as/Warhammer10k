#include "BFS.h"
#include "Graph.h"

BFS::BFS(const Graph& g) : graph(g), currentNode(-1) {}

void BFS::executeBFS(int initialNode) {
    if (this->firstCall) {
        this->reset();
        if (initialNode < 0 || initialNode >= this->graph.getNodeCount()) return;
        this->visited.insert(initialNode);
        this->lastLayer = this->graph.getNeighbors(initialNode);
        for (int v : lastLayer) {
            this->visited.insert(v);
        }
        this->firstCall = false;
    } else {
        if (this->lastLayer.empty()) return;
        std::set<int> nextLayerSet;
        for (int v : lastLayer) {
            for (int n : this->graph.getNeighbors(v)) {
                if (this->visited.find(n) == this->visited.end()) {
                    nextLayerSet.insert(n);
                }
            }
        }
        this->lastLayer = std::vector<int>(nextLayerSet.begin(), nextLayerSet.end());
        for (int v : lastLayer) {
            this->visited.insert(v);
        }
        
    }
}

std::vector<int> BFS::getCloseNeighbors() {
    return this->lastLayer;
}

void BFS::reset() {
    while (!this->queue.empty()) this->queue.pop();
    this->visited.clear();
    this->currentNode = -1;
    this->firstCall = true;
    this->lastLayer.clear();
}
