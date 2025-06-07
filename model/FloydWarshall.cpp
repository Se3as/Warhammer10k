#include "FloydWarshall.h"

vector<vector<size_t>> floydWarshall(size_t numPlanets, const vector<vector<size_t>> &adj, vector<bool> pVisited, size_t& iterations) {
    vector<vector<size_t>> dist = adj;

    for (size_t i = 0; i < numPlanets; ++i) {
        dist[i][i] = 0;
    }

    for (size_t i = 0; i < numPlanets; ++i) {
        if (!pVisited[i]) {
            for (size_t j = 0; j < numPlanets; ++j) {
                iterations++;
                dist[i][j] = INVALIDO;
                dist[j][i] = INVALIDO;
            }
        }
    }

    for (size_t k = 0; k < numPlanets; ++k) {
        if (!pVisited[k]) {
            continue;
        }
        for (size_t i = 0; i < numPlanets; ++i) {
            for (size_t j = 0; j < numPlanets; ++j) {
                iterations++;
                if (dist[i][k] == INVALIDO || dist[k][j] == INVALIDO) {
                    continue;
                }
                size_t newDist = dist[i][k] + dist[k][j];
                if (newDist < dist[i][j]) {
                    dist[i][j] = newDist;
                }
            }
        }
    }

    return dist;
}