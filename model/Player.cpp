#include "Player.h"
#include "Explorer.h"
#include "Starship.h"
#include "Cartographer.h"

Player::Player(size_t numPlanets): pVisited(numPlanets,false){
    pVisited[0] = true;
    units.push_back(new Pathﬁnder("Pathfinder", 10));
    units.push_back(new StarMapper("StarMapper", 10));
    units.push_back(new LightAssault("LightAssault", 10));
    units.push_back(new MediumAssault("MediumAssault", 10));
    units.push_back(new HeavyAssault("HeavyAssault", 10));
    units.push_back(new SupHeavyAssault("SupHeavyAssault", 10));
    units.push_back(new RapidSight("RapidSight", 10));
    units.push_back(new DeepProbe("DeepProbe", 10));

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

size_t Player:: attack(int index, const vector<vector<Edge>>& adj,
    size_t origin, size_t destination){
    return this->units[index]->attack_iterations(adj,
        pVisited, origin, destination);
}