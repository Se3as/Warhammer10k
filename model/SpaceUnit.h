#pragma once

#include <iostream>
#include <string>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Math.h"
using namespace std;

class SpaceUnit {
private:

    string name;
    int price;

public:
    SpaceUnit(string n, int p): name(n), price(p) {}
    virtual ~SpaceUnit() {}

    int getPrice();
    void setPrice(int p);
    string getName();
    void setName(string n);
    
    virtual size_t attack_iterations(const vector<vector<Edge>>& adj,
        vector<bool>& visited, size_t origin, size_t destination) {}
        
    virtual vector<size_t> explore(vector<bool>& visited, 
        const vector<vector<Edge>>& adj, size_t origin, size_t& iterations) {}

    virtual size_t map_neighbor(size_t numPlanets, const vector<vector<Edge>>& adj,
        size_t origin, size_t destination, vector<bool> visited, size_t& iterations) {}

    virtual vector<vector<size_t>> map_all(size_t numPlanets,
        const vector<vector<size_t>> &dist, vector<bool> pVisited, size_t& iterations) {}
};
