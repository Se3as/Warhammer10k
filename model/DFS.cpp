#include "DFS.h"

vector<size_t> dfs(size_t planet, vector<bool>& visited, vector<vector<Edge>>& adj, int depth, int maxDepth) {
    vector<size_t> newPVisited;

    if (depth > maxDepth) return newPVisited;

    visited[planet] = true;

    for (const auto& edge : adj[planet]) {
        size_t neighborPlanet = edge.id;

        if (!visited[neighborPlanet]) {
            auto partialPath = dfs(neighborPlanet, visited, adj, depth + 1, maxDepth);
            newPVisited.insert(newPVisited.end(), partialPath.begin(), partialPath.end());
        }
    }

    return newPVisited;
}