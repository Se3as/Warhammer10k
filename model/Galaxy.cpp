#include "Galaxy.h"
#include <cstdlib> 
#include <ctime>     

Galaxy::Galaxy(string name):
    name(name), graph(0){
        srand(time(0));
    }



void Galaxy:: addPlanet(Planet* planet, size_t index, string entryPlanet, 
    string exitPlanet){
    planetarium.push_back(planet);
    if(planet->getName() == entryPlanet){
        this->entryPlanet = index;
    }
    else if (planet->getName() == exitPlanet){
        this->exitPlanet = index;
    }
}

void Galaxy::makeConnections() {
    size_t n = planetarium.size();
    this->graph = Graph(n);

    vector<bool> connected(n, false);
    connected[0] = true;
    
    for (size_t i = 1; i < n; i++) {
        size_t j = rand() % i; 
        size_t origin = planetarium[j]->getSectorID();
        size_t destination = planetarium[i]->getSectorID();
        this->graph.addCon(origin, destination, 1);
        connected[i] = true;
    }

    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            if (this->graph.hasEdge(i, j)) continue;

            if (rand() % 3 < 1) {  
                size_t origin = planetarium[i]->getSectorID();
                size_t destination = planetarium[j]->getSectorID();
                this->graph.addCon(origin, destination, 1);
            }
        }
    }
}

Graph& Galaxy:: getGraph(){
    return this->graph;
}

void Galaxy::printer() {
    
    this->graph.printList();
    this->graph.printMat();
    
}

const Planet* Galaxy::getPlanet(int index) const{
    return planetarium[index];
}

const int Galaxy::getGalaxySize(){
    return planetarium.size();
}
const vector<Planet*>& Galaxy:: getPlanets() const{
    return planetarium;
}
const size_t& Galaxy:: getEntryPlanet() const{
    return this->entryPlanet;
}

const size_t& Galaxy:: getExitPlanet() const{
    return this->exitPlanet;
}

Galaxy::~Galaxy() {

}