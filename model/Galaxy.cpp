#include "Galaxy.h"

Galaxy::Galaxy(string name, string entryPlanet, string exitPlanet):
    name(name), entryPlanet(entryPlanet), exitPlanet(exitPlanet) , graph(0){}

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

void Galaxy:: addPlanet(Planet* planet){
    int posX = planet->getPosX();
    int posY = planet->getPosY();
    if (posX < this->latitude && posY < this->longitude) {
        planetarium[posX][posY] = planet;
    }
    planets.push_back(planet);

}

void Galaxy:: makeConnections(){
    this->graph = Graph(planets.size());
    for (int i = 0; i < planets.size(); i++){
        for (int j = i + 1; j < planets.size(); j++){
            int pOrigen = planets[i]->getSectorID();
            int pDestino = planets[j]->getSectorID();
            // Solo para representar que existe la connexion, no es la distancia real
            int distancia = 1;

            this->graph.addCon(pOrigen, pDestino, distancia);
        }
    }
    for (int i = 0; i < planets.size(); i++){
        for (int j = i + 1; j < planets.size(); j++){
            int pOrigen = planets[i]->getSectorID();
            int pDestino = planets[j]->getSectorID();

            int num = rand() % 3 + 1;
            if(num == 3){
                // Falta implementar validacion para ver si es nodo articulacion
                this->graph.deleteCon(pOrigen, pDestino);
            }
        }
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

    this->graph.printList();
    this->graph.printMat();
    
    
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