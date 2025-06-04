#pragma once

#include <iostream>
#include <vector>
#include "Math.h"

using namespace std;

#define INVALID -1

class Graph {
private:
    size_t numPlanets; 
    vector<vector<size_t>> matAd; 
    vector<vector<Edge>> listAd; 

public:
    Graph(size_t numPlanets);
    vector<vector<Edge>> getListAd();
    vector<vector<size_t>> getMatAd();
    void addCon(size_t origin, size_t destination, size_t distance);
    void deleteCon(size_t origin, size_t destination);
    bool hasEdge(size_t u, size_t v);

    void printMat();
    void printList();

};