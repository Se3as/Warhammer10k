
#include "ExhaustiveSearchAcot.h"
#include <vector>
#include <limits>
#define COST_LIMIT 800 
using namespace std;

size_t dfs(const vector<vector<Edge>>& adj, vector<bool>& visited, size_t current, size_t destination , size_t& iterations,
      size_t cost, size_t& best_cost) {
    iterations++;
    if (cost > COST_LIMIT || cost >= best_cost)
        return best_cost;

    if (current == destination)
        return best_cost = min(best_cost, cost);

    visited[current] = true;

    for (const Edge& edge : adj[current]) {
        if (!visited[edge.id]) {
            dfs(adj, visited, edge.id, destination,iterations, cost + edge.dist, best_cost);
        }
    }

    visited[current] = false;  
    return best_cost;
}

size_t exaSearchAcot(const vector<vector<Edge>>& adj, vector<bool>&, size_t origin, size_t destination,
      size_t& iterations) {
    vector<bool> visited(adj.size(), false);
    size_t best_cost = numeric_limits<size_t>::max();
    best_cost = dfs(adj, visited, origin, destination, iterations, 0, best_cost);
    return best_cost;
}
