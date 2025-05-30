#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Planet {

private:

    string name;

    int sectorID;

    int posX;
    int posY;

    vector<int> warps;

    Planet* N;
    Planet* S;
    Planet* E;
    Planet* W;

public:
    Planet(string name);
    ~Planet();

    void setSectorID(int id);

    int getSectorID() const;

    void setWarp(int w);

    int getWarps(int id);

    void setPosX(int x);
    void setPosY(int y);

    int getPosX() const;
    int getPosY() const;

};