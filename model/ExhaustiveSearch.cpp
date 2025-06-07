#include "ExhaustiveSearch.h"
#include <vector>
#include <limits>
using namespace std;

size_t exaSearch(const vector<vector<Edge>>& adj,
                 vector<bool>& visited,
                 size_t origin,
                 size_t destination , size_t& iterations) {
    // iterations++;
    if (origin == destination)
        return 0;

    visited[origin] = true;
    size_t best = numeric_limits<size_t>::max();

    for (const Edge& edge : adj[origin]) {
        if (!visited[edge.id]) {
            size_t result = exaSearch(adj, visited, edge.id, destination, iterations);
            if (result != numeric_limits<size_t>::max()) {
                best = min(best, edge.dist + result);
            }
        }
    }

    visited[origin] = false; // Backtrack
    return best;
}