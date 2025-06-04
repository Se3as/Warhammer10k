#include "Planet.h"

Planet::Planet(string name, int x, int y, size_t id) : name(name), posX(x), posY(y), sectorID(id){}



void Planet::setSectorID(size_t id){
    sectorID = id;
}

size_t Planet::getSectorID() const {
    return sectorID;
}

void Planet::setPosX(int x){
    posX = x;
}

void Planet::setPosY(int y){
    posY = y;
}

int Planet::getPosX() const {
    return posX;
}

int Planet::getPosY() const {
    return posY;
}

Planet::~Planet() {
    
}