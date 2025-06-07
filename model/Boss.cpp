#include "Boss.h"

Boss::Boss() : name("Horus"), life_points(100) {}


string Boss::getBossID(){
    return name;
}

void Boss::setBossHP(size_t hp){
    life_points = hp;
}

size_t Boss::getBossHP() const {
    return life_points;
}

size_t Boss:: receiveDamage(size_t damage){
    return this->life_points - damage;
}