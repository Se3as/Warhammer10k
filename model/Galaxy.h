#pragma once

#include <iostream>
#include <vector>

#include "Planet.h"

using namespace std;


class Galaxy {

private:

    string name;

    string entryPlanet;
    string exitPlanet;

    vector<vector<Planet*>> planetarium;

    static constexpr int latitude = 10;
    static constexpr int longitude = 10;


public:
    Galaxy(string name, string entryPlanet, string exitPlanet);
    ~Galaxy();

    void chartist();    //cartografo

    void addPlanet(Planet* planet, int row, int col);

    void link_probability();

    void printer();
};