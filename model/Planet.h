#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Planet {

private:

    string name;

    int posX;
    int posY;
    size_t sectorID;

    bool mapped;
    bool visited;

public:
    Planet(string name, int x, int y, size_t id);
    ~Planet();

    void setSectorID(size_t id);

    size_t getSectorID() const;
    string getName() const;
    
    void setPosX(int x);
    void setPosY(int y);

    int getPosX() const;
    int getPosY() const;

    void setMapped();
    bool getMapped();

    void setVisited();
    bool getVisited();

};