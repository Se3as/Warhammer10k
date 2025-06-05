#include "GreedySearch.h"
#include <vector>
#include <algorithm>
using namespace std;

size_t greedySearch(const vector<vector<Edge>>& adj, vector<bool>& visited, size_t origin, size_t destination) {
    size_t current = origin;
    size_t totalCost = 0;

    while (current != destination) {
        visited[current] = true;

        // Filtrar vecinos no visitados
        vector<Edge> neighbors;
        for (const Edge& edge : adj[current]) {
            if (!visited[edge.id])
                neighbors.push_back(edge);
        }

        if (neighbors.empty()) {
            // No hay camino factible
            return static_cast<size_t>(-1); // valor muy grande, error
        }

        // Selecciona el vecino con menor dist (greedy)
        auto best = min_element(neighbors.begin(), neighbors.end(), [](const Edge& a, const Edge& b) {
            return a.dist < b.dist;
        });

        totalCost += best->dist;
        current = best->id;
    }

    return totalCost;
}