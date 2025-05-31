#include <set>
#include "Model.h"
#include "Reader.h"
#include "Math.h"

#define MIN_HEADERS_CSV 3
#define MAX_X 10
#define MAX_Y 10

Model::Model(): actualGalaxy(0) {}
Model::~Model() {}

void Model::loadGalaxy(string& filename) {
    vector<vector<string>> rows = readCSV(filename);
    for (vector<string>& columns : rows) {
        if (columns.size() < MIN_HEADERS_CSV) continue;

        string galaxyName = columns[0];
        string entryPlanet = columns[1];
        string exitPlanet = columns[2];

        Galaxy galaxy(galaxyName, entryPlanet, exitPlanet);
        galaxy.chartist();

        set<pair<int, int>> takenCoordinates;
        int id = 0;
        for (size_t i = MIN_HEADERS_CSV; i < columns.size(); ++i) {
            
            pair<int, int> coord = generateUniqueCoordinate(takenCoordinates, MAX_X, MAX_Y);
            int x = coord.first;
            int y = coord.second;
            if (columns[i].empty()) continue;
            Planet* planet = new Planet(columns[i], x, y, id);
            galaxy.addPlanet(planet);
            id++;
        }
        galaxy.makeConnections();
        galaxies.push_back(move(galaxy));
    }
    
}

void Model::printGalaxy() {
    galaxies[this->actualGalaxy].printer();
}

vector<Galaxy> Model::getGalaxies() {
    return galaxies;
}