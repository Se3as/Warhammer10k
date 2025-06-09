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
    

    static constexpr int BASE_DAMAGE = 10000;
    
public:
    Model();
    ~Model();

    Player player;  // Change to private if needed
    Boss boss;
    Log log;
    duration<double> elapsed;
    void nextGalaxy();
    size_t getActualGalaxy() const;
    // Get an index of assault ship and attack the boss
    size_t attack(int index);
    vector<size_t> explore(int index);
    void loadGalaxy(string& filename);
    void printGalaxy();
    void probarBFS();
    void probarDFS();
    void probarDijkstra();
    void probarFloyd();
    int increaseEterium(int eterium);
    void setPlayerVisitedPlanets();

    size_t mapNeighbor(int index, size_t origin, size_t destination);
    vector<vector<size_t>> mapAll(int index);

    vector<Galaxy> getGalaxies();
    vector<vector<size_t>> getMatAd();

    SpaceUnit* setSpaceUnit(size_t& id) ;

    const Galaxy& getGalaxy(int index) const;

};
