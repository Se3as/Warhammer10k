#include "LocalSearch.h"
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Búsqueda local 
size_t localSearch(const vector<vector<Edge>>& adj,
                   vector<bool>& visited,
                   size_t origin,
                   size_t destination , size_t& iterations) {
    size_t current = origin;
    size_t totalCost = 0;

    while (current != destination) {
        visited[current] = true;
        size_t next = current;
        size_t minCost = numeric_limits<size_t>::max();

        for (const auto& edge : adj[current]) {
            if (!visited[edge.id] && edge.dist < minCost) {
                minCost = edge.dist;
                next = edge.id;
            }
        }

        if (next == current) {
            // No se encontró vecino no visitado con menor coste → mínimo local
            return numeric_limits<size_t>::max();
        }

        totalCost += minCost;
        current = next;
    }

    return totalCost;
}