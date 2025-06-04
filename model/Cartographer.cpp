#include "Cartographer.h"
#include "Dijkstra.h"
#include "FloydWarshall.h"


size_t Pathﬁnder:: map_neighbor(size_t numPlanets, vector<vector<Edge>>& adj, size_t origin, size_t destination){
    return dijkstra(numPlanets, adj, origin, destination);
}

 vector<vector<size_t>> StarMapper:: map_all(size_t numPlanets, vector<vector<size_t>> &dist){
    return floydWarshall( numPlanets,  dist);
}

