#include <set>
#include "Model.h"
#include "Reader.h"
#include "Math.h"
#include "Explorer.h"
#include "Starship.h"
#include "Cartographer.h"
#include "SpaceUnit.h"
#include "BFS.h"
#include "DFS.h"
#include "Dijkstra.h"
#include "FloydWarshall.h"
#include "Graph.h"

#define MIN_HEADERS_CSV 3
#define MAX_X 10
#define MAX_Y 10

Model::Model(): actualGalaxy(0), player(5) {}
Model::~Model() {}

void Model::loadGalaxy(string& filename) {

    vector<Range> parts = divideWindow();

    vector<vector<string>> rows = readCSV(filename);
    for (vector<string>& columns : rows) {
        if (columns.size() < MIN_HEADERS_CSV) continue;

        string galaxyName   = columns[0];
        string entryPlanet  = columns[1];
        string exitPlanet   = columns[2];

        Galaxy galaxy(galaxyName);

        size_t id = 0;

        vector<Range> availableParts = parts;

        for (size_t i = MIN_HEADERS_CSV; i < columns.size(); ++i) {
            if (columns[i].empty()) continue;

            int idPart = generateRandomNumber(0, static_cast<int>(availableParts.size()) - 1);
            Range part   = availableParts[idPart];

            availableParts.erase(availableParts.begin() + idPart);

            pair<int, int> coord = generateUniqueCoordinate(
                { part.x_min, part.x_max },
                { part.y_min, part.y_max }
            );

            int x = coord.first;
            int y = coord.second;

            Planet* planet = new Planet(columns[i], x, y, id);
            
            galaxy.addPlanet(planet, i, entryPlanet, exitPlanet);
            id++;
        }

        galaxy.makeConnections();
        galaxies.push_back(move(galaxy));
    }
}

void Model::printGalaxy() {
    galaxies[this->actualGalaxy].printer();
}

// void Model::printAlgorithms(){
//     Graph& graph = galaxies[this->actualGalaxy].getGraph();


//  }


const Galaxy& Model::getGalaxy(int index) const {
    return galaxies[index];
}

size_t Model:: getActualGalaxy() const{
    return this->actualGalaxy;
}

vector<Galaxy> Model::getGalaxies() {
    return galaxies;
}

size_t Model:: attack(int index){
    
    Galaxy& galaxy = galaxies[actualGalaxy];
    size_t iterations = 0;
    // Cost para el log?
    size_t cost = this->player.attack( index, galaxy.getGraph().getListAd(),
    galaxy.getEntryPlanet(), galaxy.getExitPlanet(), iterations);
    // Damage porque hay que actualizar vista vida del boss
    size_t damage = BASE_DAMAGE/iterations;
    size_t bossLife = this->boss.receiveDamage(damage);
    return bossLife;
}

vector<size_t> Model:: explore(int index){
    
    Galaxy& galaxy = galaxies[actualGalaxy];
    size_t iterations = 0;
    // Cost para el log?
    vector<size_t> planetsDiscovered = this->player.explore(index, galaxy.getGraph().getListAd(),
    galaxy.getEntryPlanet(), iterations);
    // TODO: ACTUALIZAR PLANETAS VISITADOS EN PLAYER

    return planetsDiscovered;
}

// SpaceUnit* Model::setSpaceUnit(size_t& id) {
//     SpaceUnit* spaceUnit = nullptr;
//   if (id == 1) {
//        spaceUnit = new RapidSight("rapidSight", 100);
//   }
//   else if (id == 2) {
//        spaceUnit = new DeepProbe ("deepProbe", 100);  
//   }
//   else if (id == 3) {
//      spaceUnit = new Pathﬁnder ("pathfinder", 100);  
//   }
//   else if (id == 4) {
//      spaceUnit = new StarMapper ("starMapper", 100);  
//   }
//   else if (id == 5) {
//      spaceUnit = new LightAssault ("lightAssault", 100);  
//   } 
//   else if (id == 6) {
//      spaceUnit = new MediumAssault ("mediumAssault", 100);  
//   }
//     else if (id == 7) {
//      spaceUnit = new HeavyAssault ("heavyAssault", 100);  
//   } 
//   else if (id == 8) {
//      spaceUnit = new SupHeavyAssault ("supHeavyAssault", 100);  
//   }


//   return spaceUnit;
// }
