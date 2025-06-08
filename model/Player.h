#pragma once

#include <iostream>
#include <vector>
#include "SpaceUnit.h"

using namespace std;

class Player {

private:

    string name;
    vector<bool> pVisited;
    vector<bool> pMapped;
    int eterium;

public:
    Player();
    ~Player(){}
    vector<SpaceUnit*> units;
    
    void setPlayerID(string id);

    void addEterium(int coin);

    void deductEterium(int coin);

    int getEterium() const;

    void setPVisited(size_t numPlanets);

    size_t attack(int index, const vector<vector<Edge>>& adj,
    size_t origin, size_t destination, size_t& iterations);

    vector<size_t> explore(int index, const vector<vector<Edge>>& adj,
        size_t planet, size_t& iterations);

    size_t mapNeighbor(int index, size_t numPlanets, const vector<vector<Edge>>& adj,
        size_t origin, size_t destination, size_t& iterations);
    vector<vector<size_t>> mapAll(int index, size_t numPlanets, const vector<vector<size_t>> 
        &adj, size_t& iterations);

    vector<bool>& getPVisited();
    vector<bool>& getPMapped();
};