#pragma once

#include <iostream>
#include <math.h>
#include <set>

using namespace std;

struct Edge {
    size_t id;
    size_t dist;
};

int generateRandomNumber(int min, int max);

pair<int, int> generateUniqueCoordinate(set<pair<int, int>>& takenCoordinates, 
    int max_X, int max_Y);