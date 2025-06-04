#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include "Math.h"

using namespace std;


struct Node {
    size_t planet;
    size_t distance;

    bool operator<(const Node& other) const {
        return distance > other.distance;
    }
};

size_t dijkstra(size_t numPlanets, const vector<vector<Edge>>& adj, size_t origin, size_t destination);
