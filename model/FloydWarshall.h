#pragma once

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

#include "Planet.h"



using namespace std;

class StarMapper {

private:

    vector<Planet*> planets_;
    vector<std::vector<int>> cost_matrix_;  // Matriz de costos mínimos
    vector<std::vector<Planet*>> next_;     // Matriz para reconstruir rutas

    // Método auxiliar para inicializar matrices
    void initializeMatrices();

public:
    // Constante: coste en Éterium para activar el algoritmo
    static const int FLOYD_ETHER_COST = 500;  // Ejemplo: ajusta según tu juego

    // Constructor: recibe la lista de planetas explorados
    StarMapper(const std::vector<Planet*>& planets);

    // Calcula la matriz de costos mínimos (Floyd-Warshall)
    void computeFloydWarshall();

    // Devuelve el costo mínimo entre dos planetas (-1 si no hay ruta)
    int getMinCost(Planet* start, Planet* target) const;

    // Devuelve la ruta reconstruida entre dos planetas
    std::vector<Planet*> getPath(Planet* start, Planet* target) const;

    

};