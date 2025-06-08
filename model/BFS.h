#include <iostream>
#include <vector>
#include "Math.h"
using namespace std;

vector<size_t> bfs_neighbors(vector<bool>& pVisited, const vector<vector<Edge>>& adj, size_t planet, size_t& iterations);
