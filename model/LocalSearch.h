#include <iostream>
#include <vector>
#include "Math.h"
using namespace std;

size_t localSearch(const vector<vector<Edge>>& adj, vector<bool>& visited, size_t origin, size_t destination,
       size_t& iterations);