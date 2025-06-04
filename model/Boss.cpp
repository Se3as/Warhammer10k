#include "Boss.h"

Boss::Boss() : name("Horus"), life_points(100) {}


string Boss::getBossID(){
    return name;
}

void Boss::setBossHP(int hp){
    life_points = hp;
}

int Boss::getBossHP() const {
    return life_points;
}