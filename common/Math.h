#pragma once

#include <iostream>
#include <math.h>
#include <set>
#include <vector>

using namespace std;

struct Edge {
    size_t id;
    size_t dist;
};

struct Range {
    int x_min, x_max;
    int y_min, y_max;
};

int generateRandomNumber(int min, int max);
vector<Range> divideWindow();

pair<int, int> generateUniqueCoordinate(
    const pair<int, int>& xRange,
    const pair<int, int>& yRange);
