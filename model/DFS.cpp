#include "DFS.h"
#include "DFS.h"

vector<size_t> dfs_set_depth(vector<bool>& visited, const vector<vector<Edge>>& adj,
    size_t planet, size_t& iterations){
    const int maxDepth = 3;
    int depth = 0;
    return dfs_acot( visited, adj, planet, iterations, depth, maxDepth);
}

vector<size_t> dfs_acot( vector<bool>& visited, const vector<vector<Edge>>& adj,
    size_t planet, size_t& iterations, int& depth, int maxDepth){
    vector<size_t> result;

    if (depth >= maxDepth)
        return result;

    ++iterations;

    if (!visited[planet]) {
        visited[planet] = true;
        result.push_back(planet);
        ++depth;
        if (depth >= maxDepth)
            return result;
    }

    for (const Edge& e : adj[planet]) {
        if (depth >= maxDepth)
            break;
        size_t neighbor = e.id;
        if (!visited[neighbor]) {
            auto sub = dfs_acot(visited, adj, neighbor, iterations, depth, maxDepth);
            result.insert(result.end(), sub.begin(), sub.end());
        }
    }

    return result;
}

