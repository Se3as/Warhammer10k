#include "BFS.h"

vector<size_t> BFS::bfs_neighbors( const vector<vector<size_t>>& adj, size_t planet) {
    vector<size_t> neighbors;
    neighbors.reserve(adj[planet].size());

    for (const auto& edge : adj[planet]) {
        size_t neighborPlanet = edge;
        neighbors.push_back(neighborPlanet);
    }

    return neighbors;
}