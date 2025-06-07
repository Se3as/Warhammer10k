#include "Starship.h"
#include "GreedySearch.h"
#include "LocalSearch.h"
#include "ExhaustiveSearch.h"
#include "ExhaustiveSearchAcot.h"

size_t LightAssault:: attack_iterations(const vector<vector<Edge>>& adj,
    vector<bool>& visited, size_t origin, size_t destination, size_t& iterations) {
        return greedySearch(adj, visited, origin, destination, iterations );
}

size_t MediumAssault:: attack_iterations(const vector<vector<Edge>>& adj,
    vector<bool>& visited, size_t origin, size_t destination, size_t& iterations) {
        return localSearch(adj, visited, origin, destination, iterations );
}

size_t HeavyAssault:: attack_iterations(const vector<vector<Edge>>& adj,
    vector<bool>& visited, size_t origin, size_t destination, size_t& iterations) {
        return exaSearch(adj, visited, origin, destination, iterations );
}

size_t SupHeavyAssault:: attack_iterations(const vector<vector<Edge>>& adj,
    vector<bool>& visited, size_t origin, size_t destination, size_t& iterations) {
        return exaSearchAcot(adj, visited, origin, destination, iterations );
}