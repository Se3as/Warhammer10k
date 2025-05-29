#pragma once

#include <iostream>

using namespace std;

class Planet {

private:

    string name;

    int posX;
    int posY;

    Planet* N;
    Planet* S;
    Planet* E;
    Planet* W;

public:
    Planet(string name);
    ~Planet();

    void setPosX(int x);
    void setPosY(int y);

    int getPosX() const;
    int getPosY() const;

    void setNorth(Planet* n);
    void setSouth(Planet* s);
    void setEast(Planet* e);
    void setWest(Planet* w);

    Planet* getNorth() const;
    Planet* getSouth() const;
    Planet* getEast() const;
    Planet* getWest() const;

};