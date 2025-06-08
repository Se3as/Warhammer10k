#include "Player.h"
#include "Explorer.h"
#include "Starship.h"
#include "Cartographer.h"

Player::Player(){
    eterium = 1000 ;
    pVisited = vector<bool>(0, false);
    pMapped = vector<bool>(0, false);
    units.push_back(new Pathﬁnder("Dijkstra", 10));
    units.push_back(new StarMapper("FloydWarshall", 10));
    units.push_back(new LightAssault("GreedySearch", 10));
    units.push_back(new MediumAssault("LocalSearch", 10));
    units.push_back(new HeavyAssault("ExhaustiveSearch", 10));
    units.push_back(new SupHeavyAssault("ExhaustiveSearchAcot", 10));
    units.push_back(new RapidSight("DFS", 10));
    units.push_back(new DeepProbe("BFS", 10));

}


void Player::setPlayerID(string id){
    name = id;
}

void Player::addEterium(int coin){
    eterium += coin;
}

bool Player::deductEterium(int coin) {
    bool enoughMoney = false;
    if (coin <= eterium){
        eterium - coin;
        enoughMoney = true;
    } 
    return enoughMoney;
}

int Player::getEterium() const {
    return eterium;
}

void Player::setPVisited(size_t numPlanets){
    pVisited = vector<bool>(numPlanets,false);
    pMapped = vector<bool>(numPlanets,false);
    pVisited[0] = true;
}

vector<bool>& Player:: getPVisited(){
    return this->pVisited;
}

vector<bool>& Player:: getPMapped(){
    return this->pMapped;
}

size_t Player:: attack(int index, const vector<vector<Edge>>& adj,
    size_t origin, size_t destination, size_t& iterations) {
    return this->units[index]->attack_iterations(adj,
         pVisited, origin, destination, iterations);
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