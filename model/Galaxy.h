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

    size_t entryPlanet;
    size_t exitPlanet;

    Graph graph;

    vector<Planet*> planetarium;
    
    static constexpr int latitude = 10;
    static constexpr int longitude = 10;


public:
    Galaxy(string name);
    ~Galaxy();


    void addPlanet(Planet* planet, size_t index, string entryPlanet, 
        string exitPlanet);

    void makeConnections();

    void link_probability();

    Graph& getGraph();

    const vector<Planet*>& getPlanets() const;

    const Planet* getPlanet(int index) const;
    
    const size_t& getEntryPlanet() const;
    const size_t& getExitPlanet() const;

    const int getGalaxySize();


    void printer();
};