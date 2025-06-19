#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Galaxy.h"
#include "Reader.h"
#include "SpaceUnit.h"
#include "Player.h"
#include "Boss.h"
#include "Log.h"

#include <chrono>
using namespace std::chrono;

using namespace std;

class Model {
private: 
    vector<Galaxy> galaxies;
    size_t actualGalaxy;
    
    static constexpr int BASE_DAMAGE = 100000000;
    
public:
    Model();
    ~Model();

    Player player;
    Boss boss;
    Log log;
    duration<double> elapsed;

    void loadGalaxy(string& filename);
    size_t attack(int index);
    vector<size_t> explore(int index, int planet_destination);
    size_t mapNeighbor(int index, size_t origin, size_t destination);
    vector<vector<size_t>> mapAll(int index);

    bool notFinished();
    int increaseEterium(int eterium);
    void setPlayerVisitedPlanets();

    void printGalaxy();
    void probarBFS();
    void probarDFS();
    void probarDijkstra();
    void probarFloyd();

    void nextGalaxy();
    size_t getActualGalaxy() const;
    vector<Galaxy> getGalaxies();
    vector<vector<size_t>> getMatAd();
    SpaceUnit* setSpaceUnit(size_t& id) ;
    const Galaxy& getGalaxy(int index) const;
};

