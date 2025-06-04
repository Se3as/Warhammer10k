#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Player {

private:

    string name;

    int eterium;

public:
    Player();
    ~Player();

    void setPlayerID(string id);

    void addEterium(int coin);

    int getEterium() const;
    
};