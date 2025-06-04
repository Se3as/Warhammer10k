#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Galaxy.h"
#include "Reader.h"
#include "SpaceUnit.h"

using namespace std;

class Model {
private: 
    vector<Galaxy> galaxies;
    size_t actualGalaxy;
    
public:
    Model();
    ~Model();

    void setActualGalaxy(size_t y);
    size_t getActualGalaxy() const;

    void loadGalaxy(string& filename);
    void printGalaxy();
    // void printAlgorithms();
    vector<Galaxy> getGalaxies();

    SpaceUnit* setSpaceUnit(size_t& id) ;
};
