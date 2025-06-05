#include <iostream>
#include <vector>
#include "Math.h"
using namespace std;

size_t exaSearchAcot(const vector<vector<Edge>>& adj,
    vector<bool>& visited, size_t origin, size_t destination);

size_t dfs(const vector<vector<Edge>>& adj, vector<bool>& visited,
           size_t current, size_t destination, size_t cost, size_t& best_cost);