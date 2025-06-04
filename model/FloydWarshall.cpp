#include "FloydWarshall.h"

vector<vector<size_t>> floydWarshall(size_t numPlanets, const vector<vector<size_t>> &adj) {
    
    vector<vector<size_t>> dist = adj;

    for (size_t k = 0; k < numPlanets; k++) {
        for (size_t i = 0; i < numPlanets; i++) {
            for (size_t j = 0; j < numPlanets; j++) {
                if (dist[i][k] != 1e8 && dist[k][j] != 1e8)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    return dist; 
}