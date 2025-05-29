#include "Planet.h"

Planet::Planet() : N(nullptr), S(nullptr), E(nullptr), W(nullptr) {}

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

void Planet::setNorth(Planet* n) {
    N = n;
}

void Planet::setSouth(Planet* s) {
    S = s;
}

void Planet::setEast(Planet* e) {
    E = e;
}

void Planet::setWest(Planet* w) {
    W = w;
}

Planet::~Planet() {
    
}