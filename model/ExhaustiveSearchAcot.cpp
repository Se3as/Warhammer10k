
#include "ExhaustiveSearchAcot.h"
#include <vector>
#include <limits>
#define COST_LIMIT 20 // It could change
using namespace std;

size_t exaSearchAcot(const vector<vector<Edge>>& adj,
                     vector<bool>& visited, size_t origin, size_t destination) {
    size_t best_cost = numeric_limits<size_t>::max();
    dfs(adj, visited, origin, destination, 0, best_cost);
    return best_cost;
}


size_t dfs(const vector<vector<Edge>>& adj, vector<bool>& visited,
           size_t current, size_t destination, size_t cost, size_t& best_cost) {

    if (cost > COST_LIMIT || cost >= best_cost)
        return best_cost;

    if (current == destination)
        return best_cost = min(best_cost, cost);

    visited[current] = true;

    for (const Edge& edge : adj[current]) {
        if (!visited[edge.id]) {
            dfs(adj, visited, edge.id, destination, cost + edge.dist, best_cost);
        }
    }

    visited[current] = false;  // Backtrack
    return best_cost;
}

