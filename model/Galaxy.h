#pragma once

#include <iostream>
#include <vector>
#include "Math.h"

#include "Planet.h"
#include "Graph.h"
using namespace std;


class Galaxy {

private:

    string name;

    string entryPlanet;
    string exitPlanet;

    Graph graph;

    vector<Planet*> planetarium;
    
    static constexpr int latitude = 10;
    static constexpr int longitude = 10;


public:
    Galaxy(string name, string entryPlanet, string exitPlanet);
    ~Galaxy();


    void addPlanet(Planet* planet);

    void makeConnections();

    void link_probability();

    Graph& getGraph();

    const vector<Planet*>& getPlanets() const;

    const Planet* getPlanet(int index) const;

    const int getGalaxySize();


    void printer();
};