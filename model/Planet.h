#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Planet {

private:

    string name;

    int posX;
    int posY;
    int sectorID;

public:
    Planet(string name, int x, int y, int id);
    ~Planet();

    void setSectorID(int id);

    int getSectorID() const;
    
    void setPosX(int x);
    void setPosY(int y);

    int getPosX() const;
    int getPosY() const;

};