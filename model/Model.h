#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Galaxy.h"
#include "Reader.h"

using namespace std;

class Model {
private: 
    vector<Galaxy> galaxies;
    int actualGalaxy;
    
public:
    Model();
    ~Model();

    void setActualGalaxy(int y);
    int getActualGalaxy() const;

    void loadGalaxy(string& filename);
    void printGalaxy();
    vector<Galaxy> getGalaxies();
};
