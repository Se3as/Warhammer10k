#include "Model.h"
#include "Reader.h"

Model::Model(): actualGalaxy(0) {}
Model::~Model() {}

void Model::loadGalaxy(string& filename) {
    vector<vector<string>> rows = readCSV(filename);
    for (vector<string>& columns : rows) {
        if (columns.size() < 3) continue;

        string galaxyName = columns[0];
        string entryPlanet = columns[1];
        string exitPlanet = columns[2];
        Galaxy galaxy(galaxyName, entryPlanet, exitPlanet);
        galaxy.chartist();

        int planetNum = 0;

        for (size_t i = 3; i < columns.size(); ++i) {
            if (columns[i].empty()) continue;
            Planet* planet = new Planet(columns[i]);
            int row = planetNum / 10;
            int col = planetNum % 10;
            galaxy.addPlanet(planet, row, col);
            planetNum++;
        }
        galaxies.push_back(move(galaxy));
    }
}

void Model::printGalaxy() {
    galaxies[this->actualGalaxy].printer();
}

vector<Galaxy> Model::getGalaxies() {
    return galaxies;
}