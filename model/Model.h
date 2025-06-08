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
    // size_t attack(int index);
    size_t greedyAttack(int index);
    size_t localAttack(int index);
    size_t exhaustiveAttack(int index);
    size_t exhaustiveBoundedAttack(int index);
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
