#include "Galaxy.h"

Galaxy::Galaxy(string name, string entryPlanet, string exitPlanet):
    name(name), entryPlanet(entryPlanet), exitPlanet(exitPlanet) {}

void Galaxy::chartist() {

    planetarium = vector<vector<Planet*>> (latitude, vector<Planet*>
        (longitude, nullptr)) ;


    // int id = 1;
    // for (size_t i = 0; i < planetarium.size(); ++i) {
    //     for (size_t j = 0; j < planetarium[i].size(); ++j) {
    //         if (planetarium[i][j] == nullptr) {
    //             planetarium[i][j] = new Planet("earth");
    //             planetarium[i][j]->setPosX(i);
    //             planetarium[i][j]->setPosY(j);
    //             planetarium[i][j]->setSectorID(id);

    //             for(int k = 1; k <= 100; ++k){
    //                 if(planetarium[i][j]->getSectorID() != k){
    //                     planetarium[i][j]->setWarp(k);
    //                 }
    //             }
    //         }
    //         id++;
    //     }
    // }

}

void Galaxy:: addPlanet(Planet* planet, int row, int col){
    if (row < this->latitude && col < this->longitude) {
        planetarium[row][col] = planet;
    }
}

void Galaxy::printer() {
    
    //print for planet matriz display
    for (size_t i = 0; i < planetarium.size(); ++i) {
        for (size_t j = 0; j < planetarium[i].size(); ++j) {
            if (planetarium[i][j] != nullptr) {
                cout << "1 ";
                //cout << planetarium[i][j]->getSectorID() << " ";
            } else {
                cout << "0 ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
    
    
    //print for warps for each planet
    
    // if (planetarium[0][0] != nullptr) {
    //     cout << "\nWarps del planeta (0,0): \n";

    //     for(int k = 0; k < 99; ++k){
    //         if(planetarium[0][0]->getSectorID() != k){
    //             cout<< planetarium[0][0]->getWarps(k) << " ";
    //         }
    //     }
    // }
}


Galaxy::~Galaxy() {

    // //planet liberator (for the Emperor!)
    // for (size_t i = 0; i < planetarium.size(); ++i) {
    //     for (size_t j = 0; j < planetarium[i].size(); ++j) {
    //         if (planetarium[i][j] != nullptr) {
    //             delete planetarium[i][j];
    //         }
    //     }
    // }
}