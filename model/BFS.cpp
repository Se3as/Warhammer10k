#include "BFS.h"

vector<size_t> bfs_neighbors(vector<bool>& pVisited, const vector<vector<Edge>>& adj, size_t planet, size_t& iterations) {
    vector<size_t> neighbors;
    neighbors.reserve(adj[planet].size());

    for (const auto& edge : adj[planet]) {
        iterations ++;
        size_t neighborPlanet = edge.id;
        pVisited[neighborPlanet] = true;
        neighbors.push_back(neighborPlanet);
    }

    return neighbors;
}