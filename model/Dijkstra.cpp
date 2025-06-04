#include "Dijkstra.h"


std::pair<int, std::vector<Planet*>> Pathfinder::getCheapestPath(
    Planet* start, 
    Planet* target
) {


    std::unordered_map<Planet*, int> min_cost;
    std::unordered_map<Planet*, Planet*> previous_planet;
    std::priority_queue<PlanetPriority> frontier;



    // inicializa solo el nodo de partida
    min_cost[start] = 0;
    frontier.push({start, 0});

    while (!frontier.empty()) {

        Planet* current = frontier.top().planet;
        int current_cost = frontier.top().added_cost;
        frontier.pop();

        if (current_cost > min_cost[current]) continue;
        if (current == target) break;

        // for (const auto& connection : current->connections) {   //VERIFICAR USAR CONNECTIONS CUANDO LAS CONEXIONES ENTRE PLANETAS ENGAN PESO 
        //     Planet* neighbor = connection.first;
        //     int travel_cost = connection.second;
        //     int new_cost = current_cost + travel_cost;

        //     // Si el vecino no está en min_cost, se añade automáticamente con INT_MAX
        //     if (new_cost < min_cost[neighbor]) {
        //         min_cost[neighbor] = new_cost;
        //         previous_planet[neighbor] = current;
        //         frontier.push({neighbor, new_cost});
        //     }
        // }
    }

    // Reconstrucción de la ruta (igual que antes)
    std::vector<Planet*> path;
    if (min_cost.find(target) != min_cost.end() && min_cost[target] != INT_MAX) {
        Planet* current = target;
        while (current != nullptr) {
            path.push_back(current);
            current = previous_planet[current];
        }
        std::reverse(path.begin(), path.end());
    }

    return {min_cost[target], path};
}