#include <iostream>
#include <vector>
#include "Math.h"

using namespace std;

size_t exaSearch(const vector<vector<Edge>>& adj,
    vector<bool>& visited, size_t origin, size_t destination);
    