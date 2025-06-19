#include "Cartographer.h"
#include "Dijkstra.h"
#include "FloydWarshall.h"

size_t Mapper:: map_neighbor(size_t numPlanets, const vector<vector<Edge>>& adj, size_t origin, size_t destination, vector<bool> pVisited, size_t& iterations){
    return 0;
}
vector<vector<size_t>> Mapper:: map_all(size_t numPlanets, const vector<vector<size_t>> &dist, vector<bool> pVisited, size_t& iterations){
    return {};
}

size_t Pathﬁnder:: map_neighbor(size_t numPlanets, const vector<vector<Edge>>& adj, size_t origin, size_t destination, vector<bool>pVisited, size_t& iterations){
    return dijkstra(numPlanets, adj, origin, destination, pVisited, iterations);
}

 vector<vector<size_t>> StarMapper:: map_all(size_t numPlanets, const vector<vector<size_t>> &dist, vector<bool> pVisited, size_t& iterations){
    return floydWarshall( numPlanets,  dist, pVisited, iterations);
}