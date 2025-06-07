#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Galaxy.h"
#include "Reader.h"
#include "SpaceUnit.h"
#include "Player.h"
#include "Boss.h"

using namespace std;

class Model {
private: 
    vector<Galaxy> galaxies;
    size_t actualGalaxy;
    Player player;
    Boss boss;

    static constexpr int BASE_DAMAGE = 1000;
    
public:
    Model();
    ~Model();

    void setActualGalaxy(size_t y);
    size_t getActualGalaxy() const;
    size_t attack(int index);
    vector<size_t> explore(int index);
    void loadGalaxy(string& filename);
    void printGalaxy();
    // void printAlgorithms();
    vector<Galaxy> getGalaxies();

    SpaceUnit* setSpaceUnit(size_t& id) ;

    const Galaxy& getGalaxy(int index) const;

};
