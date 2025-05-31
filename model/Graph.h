#pragma once

#include <iostream>
#include <vector>

using namespace std;

#define INVALID -1

class Graph {
private:
    int numPlanetas; 
    vector<vector<int>> matAd; 
    vector<vector<pair<int, int>>> listAd; 

public:
    Graph(int numPlanetas);

    void addCon(int iPO, int iPD, int distancia);
    void deleteCon(int iPO, int iPD);

    void printMat();
    void printList();

};