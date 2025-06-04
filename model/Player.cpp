#include "Player.h"

Player::Player(size_t numPlanets): pVisited(numPlanets,false){
    pVisited[0] = true;
}


void Player::setPlayerID(string id){
    name = id;
}

void Player::addEterium(int coin){
    eterium += coin;
}


int Player::getEterium() const {
    return eterium;
}

void Player::addPVisited(size_t pVisitado){
    this->pVisited[pVisitado] = true;
}

vector<bool> Player:: getPVisited(){
    return this->pVisited;
}