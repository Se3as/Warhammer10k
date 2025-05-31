#pragma once

#include <vector>
#include <unordered_map>
#include <queue>         
#include <algorithm>
#include <climits>  

#include "Planet.h"

using namespace std;

class Pathfinder {

private:

    struct PlanetPriority {
        Planet* planet;
        int added_cost;  // acumulacion de Etereum 

        // Sobrecarga para que la priority_queue sea un min-heap
        bool operator<(const PlanetPriority& other) const {
            return added_cost > other.added_cost;  //">" me da la prioridad menor
        }
    };

public:
    
    pair<int, vector<Planet*>> getCheapestPath(Planet* start, Planet* target);

};