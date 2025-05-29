#include "Galaxy.h"

Galaxy::Galaxy(string name, string entryPlanet, string exitPlanet):
    name(name), entryPlanet(entryPlanet), exitPlanet(exitPlanet) {}

void Galaxy::chartist() {

    planetarium = vector<vector<Planet*>> (latitude, vector<Planet*>
        (longitude, nullptr)) ;

}

void Galaxy:: addPlanet(Planet* planet, int row, int col){
    if (row < this->latitude && col < this->longitude) {
        planetarium[row][col] = planet;
    }
}


void Galaxy::printer() {
    
    for (int i = 0; i < planetarium.size(); ++i) {
        for (int j = 0; j < planetarium[i].size(); ++j) {
            if (planetarium[i][j] != nullptr) {
                std::cout << "1 ";
            } else {
                std::cout << "0 ";
            }
        }
        std::cout << "\n";
    }
    
}

Galaxy::~Galaxy() {

}