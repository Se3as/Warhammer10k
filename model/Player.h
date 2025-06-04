#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Player {

private:

    string name;
    vector<bool> pVisited;
    int eterium;

public:
    Player(size_t numPlanets);
    ~Player();

    void setPlayerID(string id);

    void addEterium(int coin);

    int getEterium() const;

    void addPVisited(size_t);
    
    vector<bool> getPVisited();
};