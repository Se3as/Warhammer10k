#include "BFS.h"

vector<size_t> bfs_neighbors( const vector<vector<Edge>>& adj, size_t planet) {
    vector<size_t> neighbors;
    neighbors.reserve(adj[planet].size());

    for (const auto& edge : adj[planet]) {
        size_t neighborPlanet = edge.id;
        neighbors.push_back(neighborPlanet);
    }

    return neighbors;
}