
#include <limits>
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
            
            galaxy.addPlanet(planet, id, entryPlanet, exitPlanet);
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

size_t Model::attack(int index) {
    Galaxy& galaxy = galaxies[actualGalaxy];
    size_t iterations = 0;

    // Previsualización del coste de entry planet hasta exit planet
    auto adj = galaxy.getGraph().getListAd();
    std::cout << "Adjacency list for entry planet (" << galaxy.getEntryPlanet() << "): ";
    for (const auto& edge : adj[galaxy.getEntryPlanet()]) {
        std::cout << "(to " << edge.id << ", dist " << edge.dist << ") ";
    }
    std::cout << std::endl;

    std::cout << "Entry planet: " << galaxy.getEntryPlanet() << ", Exit planet: " << galaxy.getExitPlanet() << std::endl;

    for (size_t i = 0; i < adj.size(); ++i) {
        std::cout << "Planet " << i << ": ";
        for (const auto& edge : adj[i]) {
            std::cout << "(to " << edge.id << ", dist " << edge.dist << ") ";
        }
        std::cout << std::endl;
    }

    size_t cost = this->player.attack(index, adj,
                                      galaxy.getEntryPlanet(), galaxy.getExitPlanet(), iterations);
    // Log del coste de ataque usando greedy
    // std::cout << "Cost of attack using greedy search: " << cost << std::endl;

    std::cout << "Cost of attack: " << cost << std::endl;
    
    // Si el coste es infinito, significa que no se encontró un camino
    if (cost == std::numeric_limits<size_t>::max()) {
        std::cout << "No path found for attack!" << std::endl;
        return this->boss.getBossHP(); // Don't deal damage if no path
    }


    // Log de iteraciones
    std::cout << "Iterations: " << iterations << std::endl;

    size_t damage = 0;
    if (iterations > 0) {
        // Log del cálculo de daño
        damage = BASE_DAMAGE / (iterations * iterations);
    } 
    // Log del daño
    std::cout << "Damage dealt: " << damage << std::endl;

    // Log de vida del boss
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
