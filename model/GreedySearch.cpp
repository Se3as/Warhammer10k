#include "GreedySearch.h"
#include <queue>
#include <set>
#include <algorithm>
#include <cstdint>

size_t greedySearch(const vector<vector<Edge>>& adj,
                    vector<bool>& visited, size_t origin, size_t destination) {
    if (origin == destination) {
        return 0; // No distance if origin is the same as destination
    }

    // Sort neighbors by lowest immediate cost
    vector<Edge> neighbors = adj[origin];
    std::sort(neighbors.begin(), neighbors.end(), [](const Edge &a, 
        const Edge &b) {
        return a.dist < b.dist;
    });

    for (const Edge &neighbor : neighbors) {
        if (!visited[neighbor.id]) {
            visited[neighbor.id] = true;
            size_t result = greedySearch(adj, visited, neighbor.id, destination);
            if (result != SIZE_MAX) {
                return result + neighbor.dist;
            }
        }
    }

    return SIZE_MAX;
}