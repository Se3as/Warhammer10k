#include <iostream>
#include <vector>
#include "Math.h"
using namespace std;

class DFS {
  public:
    vector<size_t> dfs(size_t planet, vector<bool>& visited, vector<vector<size_t>>& adj, int depth = 0, int maxDepth = 3);
};
