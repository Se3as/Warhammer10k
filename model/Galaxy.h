#pragma once

#include <iostream>
#include <vector>

#include "Planet.h"
#include "Graph.h"
using namespace std;


class Galaxy {

private:

    string name;

    string entryPlanet;
    string exitPlanet;

    Graph graph;

    vector<vector<Planet*>> planetarium;
    vector<Planet*> planets;
    static constexpr int latitude = 10;
    static constexpr int longitude = 10;


public:
    Galaxy(string name, string entryPlanet, string exitPlanet);
    ~Galaxy();

    void chartist();    //cartografo

    void addPlanet(Planet* planet);
    void makeConnections();

    void link_probability();

    void printer();
};