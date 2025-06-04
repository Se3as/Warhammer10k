#include <iostream>
#include <vector>
#include "Math.h"
using namespace std;

vector<size_t> dfs(size_t planet, vector<bool>& visited, vector<vector<Edge>>& adj, int depth = 0, int maxDepth = 3); 