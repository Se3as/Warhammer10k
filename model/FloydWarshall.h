#include <iostream>
#include <vector>
#include <limits>
using namespace std;

static constexpr size_t INVALIDO = numeric_limits<size_t>::max();

vector<vector<size_t>> floydWarshall(size_t numPlanets, const vector<vector<size_t>> &adj,vector<bool> pVisited, size_t& iterations);