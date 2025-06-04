#include "FloydWarshall.h"


StarMapper::StarMapper(const std::vector<Planet*>& planets) : planets_(planets) {
    initializeMatrices();
    computeFloydWarshall();
}

// Inicializa las matrices de costos y rutas
void StarMapper::initializeMatrices() {
    int n = planets_.size();
    cost_matrix_.resize(n, std::vector<int>(n, INT_MAX));
    next_.resize(n, std::vector<Planet*>(n, nullptr));

    // Diagonal principal: costo 0
    for (int i = 0; i < n; ++i) {
        cost_matrix_[i][i] = 0;
    }




    // // Llenar con conexiones directas entre planetas
    // for (int i = 0; i < n; ++i) {
    //     Planet* planet = planets_[i];
    //     for (const auto& connection : planet->connections) {
    //         Planet* neighbor = connection.first;
    //         int cost = connection.second;
    //         auto it = std::find(planets_.begin(), planets_.end(), neighbor);
    //         if (it != planets_.end()) {
    //             int j = it - planets_.begin();
    //             cost_matrix_[i][j] = cost;
    //             next_[i][j] = neighbor;
    //         }
    //     }
    // }



}

// Algoritmo Floyd-Warshall
void StarMapper::computeFloydWarshall() {
    int n = planets_.size();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (cost_matrix_[i][k] != INT_MAX && 
                    cost_matrix_[k][j] != INT_MAX && 
                    cost_matrix_[i][j] > cost_matrix_[i][k] + cost_matrix_[k][j]) {
                    cost_matrix_[i][j] = cost_matrix_[i][k] + cost_matrix_[k][j];
                    next_[i][j] = next_[i][k];
                }
            }
        }
    }
}

// Obtiene el costo mínimo entre dos planetas
int StarMapper::getMinCost(Planet* start, Planet* target) const {
    auto it_start = std::find(planets_.begin(), planets_.end(), start);
    auto it_target = std::find(planets_.begin(), planets_.end(), target);
    
    if (it_start == planets_.end() || it_target == planets_.end()) {
        return -1;  // Planeta no explorado
    }

    int i = it_start - planets_.begin();
    int j = it_target - planets_.begin();
    return (cost_matrix_[i][j] == INT_MAX) ? -1 : cost_matrix_[i][j];
}

// Reconstruye la ruta entre dos planetas
std::vector<Planet*> StarMapper::getPath(Planet* start, Planet* target) const {
    std::vector<Planet*> path;
    auto it_start = std::find(planets_.begin(), planets_.end(), start);
    auto it_target = std::find(planets_.begin(), planets_.end(), target);

    if (it_start == planets_.end() || it_target == planets_.end() || 
        getMinCost(start, target) == -1) {
        return path;  // Ruta vacía si no hay camino
    }

    int i = it_start - planets_.begin();
    int j = it_target - planets_.begin();

    path.push_back(start);
    while (i != j) {
        i = std::find(planets_.begin(), planets_.end(), next_[i][j]) - planets_.begin();
        path.push_back(planets_[i]);
    }

    return path;
}