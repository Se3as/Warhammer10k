#include "Planet.h"

Planet::Planet(string name, int x, int y, size_t id) : name(name), posX(x), posY(y), sectorID(id), mapped(false){}



void Planet::setSectorID(size_t id){
    sectorID = id;
}

size_t Planet::getSectorID() const {
    return sectorID;
}

void Planet::setMapped(){
    mapped = true;
}

bool Planet::getMapped(){
    return mapped;
}

void Planet::setVisited(){
    visited = true;
}

bool Planet::getVisited(){
    return visited;
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

string Planet::getName() const {
    return name;
}

Planet::~Planet() {
    
}