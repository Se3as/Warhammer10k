#include "SpaceUnit.h"

int SpaceUnit::getPrice(){
    return price;
}
void SpaceUnit::setPrice(int p){
    price = p;
}
string SpaceUnit::getName(){
    return name;
}
void SpaceUnit::setName(string n){
    name = n;
}

size_t SpaceUnit:: attack_iterations(const vector<vector<Edge>>& adj,
    vector<bool>& visited, size_t origin, size_t destination, size_t& iterations) {
    return 0;
}

vector<size_t> SpaceUnit::explore(vector<bool>& visited,
    const vector<vector<Edge>>& adj, size_t origin, size_t& iterations, int planet_destination) {
    return {};
}

size_t SpaceUnit:: map_neighbor(size_t numPlanets, const vector<vector<Edge>>& adj,
    size_t origin, size_t destination, vector<bool> visited, size_t& iterations) {
    return 0;
}

vector<vector<size_t>> SpaceUnit:: map_all(size_t numPlanets,
    const vector<vector<size_t>> &dist, vector<bool> pVisited, size_t& iterations) {
    return {};
}
