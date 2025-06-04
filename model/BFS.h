#include <iostream>
#include <vector>
#include "Math.h"
using namespace std;

class BFS {
  public:
  vector<size_t> bfs_neighbors( const vector<vector<size_t>>& adj, size_t planet);
};