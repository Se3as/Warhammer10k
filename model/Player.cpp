#include "Player.h"
#include "Explorer.h"
#include "Starship.h"
#include "Cartographer.h"

Player::Player(){
    pVisited = vector<bool>(0, false);
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

void Player::setPVisited(size_t numPlanets){
    pVisited = vector<bool>(numPlanets,false);
    pVisited[0] = true;
}

vector<bool>& Player:: getPVisited(){
    return this->pVisited;
}

size_t Player:: attack(int index, const vector<vector<Edge>>& adj,
    size_t origin, size_t destination, size_t& iterations) {
    return this->units[index]->attack_iterations(adj,
         pVisited, origin, destination);
}

vector<size_t> Player::explore(int index, const vector<vector<Edge>>& adj,
    size_t planet, size_t& iterations){
        return this->units[index]->explore( pVisited, adj, planet, iterations);
}


size_t Player:: mapNeighbor(int index, size_t numPlanets, const vector<vector<Edge>>& adj,
        size_t origin, size_t destination, size_t& iterations){
        return this->units[index]->map_neighbor(numPlanets, adj, origin, 
            destination, pVisited, iterations);
    }
vector<vector<size_t>> Player:: mapAll(int index, size_t numPlanets, const vector<vector<size_t>> 
    &adj, size_t& iterations){
    return this->units[index]->map_all(numPlanets, adj, pVisited, iterations);
}