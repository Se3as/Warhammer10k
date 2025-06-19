
#include "Explorer.h"
using namespace std;

vector<size_t> RapidSight:: explore (vector<bool>& visited, const vector<vector<Edge>>& adj, size_t origin, size_t& iterations,
int planet_destination){
    return dfs_set_depth(visited, adj, origin, iterations);
}

vector<size_t> DeepProbe:: explore(vector<bool>& visited, const vector<vector<Edge>>& adj, size_t origin, size_t& iterations,
    int planet_destination){
    return bfs_neighbors(visited, adj, planet_destination, iterations);
}
