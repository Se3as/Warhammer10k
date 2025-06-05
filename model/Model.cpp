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

Model::Model(): actualGalaxy(0) {}
Model::~Model() {}

void Model::loadGalaxy(std::string& filename) {

    std::vector<Range> parts = divideWindow();

    std::vector<std::vector<std::string>> rows = readCSV(filename);
    for (std::vector<std::string>& columns : rows) {
        if (columns.size() < MIN_HEADERS_CSV) continue;

        std::string galaxyName   = columns[0];
        std::string entryPlanet  = columns[1];
        std::string exitPlanet   = columns[2];

        Galaxy galaxy(galaxyName, entryPlanet, exitPlanet);

        std::set<std::pair<int, int>> takenCoordinates;
        size_t id = 0;

        std::vector<Range> availableParts = parts;

        for (size_t i = MIN_HEADERS_CSV; i < columns.size(); ++i) {
            if (columns[i].empty()) continue;

            int idPart = generateRandomNumber(0, static_cast<int>(availableParts.size()) - 1);
            Range part   = availableParts[idPart];

            availableParts.erase(availableParts.begin() + idPart);

            std::pair<int, int> coord = generateUniqueCoordinate(
                { part.x_min, part.x_max },
                { part.y_min, part.y_max }
            );

            int x = coord.first;
            int y = coord.second;

            Planet* planet = new Planet(columns[i], x, y, id);
            galaxy.addPlanet(planet);
            id++;
        }

        galaxy.makeConnections();
        galaxies.push_back(std::move(galaxy));
    }
}

void Model::printGalaxy() {
    galaxies[this->actualGalaxy].printer();
}

// void Model::printAlgorithms(){
//     Graph& graph = galaxies[this->actualGalaxy].getGraph();


//  }

vector<Galaxy> Model::getGalaxies() {
    return galaxies;
}

SpaceUnit* Model::setSpaceUnit(size_t& id) {
    SpaceUnit* spaceUnit = nullptr;
  if (id == 1) {
       spaceUnit = new RapidSight("rapidSight", 100);
  }
  else if (id == 2) {
       spaceUnit = new DeepProbe ("deepProbe", 100);  
  }
  else if (id == 3) {
     spaceUnit = new Pathﬁnder ("pathfinder", 100);  
  }
  else if (id == 4) {
     spaceUnit = new StarMapper ("starMapper", 100);  
  }
  else if (id == 5) {
     spaceUnit = new LightAssault ("lightAssault", 100);  
  } 
  else if (id == 6) {
     spaceUnit = new MediumAssault ("mediumAssault", 100);  
  }
    else if (id == 7) {
     spaceUnit = new HeavyAssault ("heavyAssault", 100);  
  } 
  else if (id == 8) {
     spaceUnit = new SupHeavyAssault ("supHeavyAssault", 100);  
  }


  return spaceUnit;
}
