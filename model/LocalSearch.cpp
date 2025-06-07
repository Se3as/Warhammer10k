#include "LocalSearch.h"
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

// Helper function: recursive greedy DFS with backtracking
size_t greedyBacktrack(const vector<vector<Edge>>& adj, vector<bool>& visited, size_t current, size_t destination, size_t& iterations) {
    if (current == destination) return 0;
    visited[current] = true;
    iterations++;

    // Get all unvisited neighbors
    vector<Edge> neighbors;
    for (const Edge& edge : adj[current]) {
        if (!visited[edge.id])
            neighbors.push_back(edge);
    }

    // Sort neighbors by distance (greedy: try shortest first)
    sort(neighbors.begin(), neighbors.end(), [](const Edge& a, const Edge& b) {
        return a.dist < b.dist;
    });

    vector<size_t> allCosts; // Store all possible path costs

    for (const Edge& edge : neighbors) {
        size_t cost = greedyBacktrack(adj, visited, edge.id, destination, iterations);
        if (cost != numeric_limits<size_t>::max()) {
            allCosts.push_back(edge.dist + cost);
        }
    }

    visited[current] = false; // Backtrack

    // Return the minimum cost among all possible paths, or max if none
    if (!allCosts.empty()) {
        return *min_element(allCosts.begin(), allCosts.end());
    } else {
        return numeric_limits<size_t>::max();
    }
}

size_t localSearch(const vector<vector<Edge>>& adj,
                   vector<bool>& /*visited*/,
                   size_t origin,
                   size_t destination, size_t& iterations) {
    vector<bool> visited(adj.size(), false);
    iterations = 0;
    return greedyBacktrack(adj, visited, origin, destination, iterations);
}