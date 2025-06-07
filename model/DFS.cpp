#include "DFS.h"


vector<size_t> dfs_set_depth(vector<bool>& visited, const vector<vector<Edge>>& adj, size_t planet,size_t& iterations){
    int depth = 0;
    int maxDepth = 3;
    vector<size_t> newPVisited = dfs_acot(visited, adj, planet, iterations, depth, maxDepth);
    depth = 0;
    return newPVisited;
}
vector<size_t> dfs_acot(vector<bool>& visited, const vector<vector<Edge>>& adj,size_t planet,size_t& iterations, int& depth, int maxDepth) {
    iterations++;
    vector<size_t> newPVisited;

    if (depth > maxDepth) 
        return newPVisited;

    if (!visited[planet]) {
        visited[planet] = true;
        newPVisited.push_back(planet);
        depth++;
    }

    for (size_t i = 0; i < adj[planet].size(); ++i) {
        if (depth >= maxDepth) 
            break;
        const Edge& neighbor = adj[planet][i];
        if (!visited[neighbor.id]) {
            vector<size_t> pVisitedInc = dfs_acot(visited, adj,neighbor.id, iterations, depth, maxDepth);
            newPVisited.insert(newPVisited.end(), pVisitedInc.begin(), pVisitedInc.end());
        }
    }

    return newPVisited;
}
