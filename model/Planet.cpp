#include "Planet.h"

Planet::Planet(string name) : name(name), N(nullptr), S(nullptr), E(nullptr), W(nullptr) {}



void Planet::setSectorID(int id){
    sectorID = id;
}

int Planet::getSectorID() const {
    return sectorID;
}

void Planet::setWarp(int w){
    warps.push_back(w);
}

int Planet::getWarps(int id){
    return warps[id];
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