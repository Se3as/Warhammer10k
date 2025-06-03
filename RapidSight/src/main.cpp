#include <iostream>
#include <set>
#include "Graph.h"
#include "BFS.h"

#define NUMBERS 5
int main() {
    // Crear y configurar grafo
    Graph graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);

    BFS bfs(graph);

    bfs.executeBFS(1); // Step 1: direct neighbors
    std::cout << "Neighbors of node 1: ";
    for (int v : bfs.getCloseNeighbors()) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    bfs.executeBFS(1); // Step 2: non-direct neighbors
    std::cout << "Neighbors of node 1: ";
    for (int v : bfs.getCloseNeighbors()) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    bfs.executeBFS(1); // Step 2: non-direct neighbors
    std::cout << "Neighbors of node 1: ";
    for (int v : bfs.getCloseNeighbors()) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    return 0;
}