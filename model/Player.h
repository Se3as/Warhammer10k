#pragma once

#include <iostream>
#include <vector>
#include "SpaceUnit.h"

using namespace std;

class Player {

private:

    string name;
    vector<bool> pVisited;
    int eterium;
    vector<SpaceUnit*> units;
public:
    Player(size_t numPlanets);
    ~Player(){}

    void setPlayerID(string id);

    void addEterium(int coin);

    int getEterium() const;

    void addPVisited(size_t);

    size_t attack(int index, const vector<vector<Edge>>& adj,
    size_t origin, size_t destination);
    
    vector<bool> getPVisited();
};