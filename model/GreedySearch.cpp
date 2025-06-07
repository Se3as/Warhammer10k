#include "GreedySearch.h"
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
using namespace std;

size_t greedySearch(const vector<vector<Edge>>& adj, vector<bool>& /*visited*/, size_t origin, size_t destination, size_t& iterations) {
    size_t current = origin;
    size_t totalCost = 0;
    vector<bool> visited(adj.size(), false);

    while (current != destination) {
        iterations++;  // count each iteration
        visited[current] = true;

        // Get all unvisited neighbors
        vector<Edge> neighbors;
        for (const Edge& edge : adj[current]) {
            if (!visited[edge.id])
                neighbors.push_back(edge);
        }
        /*
        std::cout << "Current: " << current << ", neighbors: ";
        for (const Edge& edge : neighbors) {
            std::cout << edge.id << " ";
        }
        std::cout << std::endl;
        */

        // No encontró vecinos no visitados porque siempre escoge el camino con
        // menos costo, por eso no hay camino
        if (neighbors.empty()) {
            std::cout << "GreedySearch: No path found from " << current << std::endl;
            return std::numeric_limits<size_t>::max();
        }

        // Select the neighbor with the smallest distance (greedy)
        auto best = min_element(neighbors.begin(), neighbors.end(), [](const Edge& a, const Edge& b) {
            return a.dist < b.dist;
        });

        totalCost += best->dist;
        current = best->id;
    }

    return totalCost;
}