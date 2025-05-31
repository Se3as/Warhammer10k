#include "Player.h"

Player::Player(){}



void Player::setPlayerID(string id){
    name = id;
}

void Player::addEterium(int coin){
    eterium += coin;
}


int Player::getEterium() const {
    return eterium;
}