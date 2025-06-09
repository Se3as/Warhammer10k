#include <iostream>
#include <vector>
#include "Math.h"
using namespace std;

vector<size_t> dfs_set_depth(vector<bool>& visited, const vector<vector<Edge>>& adj, size_t planet,size_t& iterations); 
vector<size_t> dfs_acot(vector<bool>& visited, const vector<vector<Edge>>& adj, size_t planet,size_t& iterations, int& depth , int maxDepth); 