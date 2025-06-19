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

Model::Model(): actualGalaxy(0){
    log.openCsv();
}
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
void Model:: setPlayerVisitedPlanets(){
    Galaxy& galaxy = galaxies[actualGalaxy];
    size_t numPlanets = galaxy.getGalaxySize();
    this->player.setPVisited(numPlanets);
}


size_t Model::attack(int index) {
    Galaxy& galaxy = galaxies[actualGalaxy];
    size_t iterations = 0;
    size_t cost = 0;

    high_resolution_clock::time_point start = high_resolution_clock::now();
    cost = this->player.attack(index, galaxy.getGraph().getListAd(),
        galaxy.getEntryPlanet(), galaxy.getExitPlanet(), iterations);
    high_resolution_clock::time_point end = high_resolution_clock::now();
    elapsed = end - start;

    if (cost == std::numeric_limits<size_t>::max()) {
        return this->boss.getBossHP(); 
    }

    size_t damage = 0;
    if (iterations > 0) {
        damage = BASE_DAMAGE / (iterations * iterations);
    }

    log.register_attack(iterations,player.units[index]->getName(), damage, elapsed.count());

    size_t bossLife = this->boss.receiveDamage(damage);
    return bossLife;
}

vector<size_t> Model:: explore(int index, int planet_destination){
    
    Galaxy& galaxy = galaxies[actualGalaxy];
    size_t iterations = 0;

    high_resolution_clock::time_point start = high_resolution_clock::now();
    vector<size_t> planetsDiscovered = this->player.explore(index, galaxy.getGraph().getListAd(),
        galaxy.getEntryPlanet(), iterations, planet_destination);
    high_resolution_clock::time_point end = high_resolution_clock::now();
    elapsed = end - start;

    log.register_noAttack(iterations,player.units[index]->getName(), elapsed.count());


    return planetsDiscovered;
}

size_t Model:: mapNeighbor(int index, size_t origin, size_t destination){
    Galaxy& galaxy = galaxies[actualGalaxy];
    size_t numPlanets = galaxy.getGalaxySize();
    size_t iterations = 0;

    high_resolution_clock::time_point start = high_resolution_clock::now();
    size_t distance = this->player.mapNeighbor(index, numPlanets, galaxy.getGraph().getListAd(),
        origin, destination, iterations);
    high_resolution_clock::time_point end = high_resolution_clock::now();
    elapsed = end - start;

    log.register_noAttack(iterations,player.units[index]->getName(), elapsed.count());

    vector<bool>& mapped = this->player.getPMapped();
    mapped[origin]= true;
    mapped[destination]= true;

    return distance;
}

vector<vector<size_t>> Model:: mapAll(int index){
    Galaxy& galaxy = galaxies[actualGalaxy];
    size_t numPlanets = galaxy.getGalaxySize();
    size_t iterations = 0;

    high_resolution_clock::time_point start = high_resolution_clock::now();
    vector<vector<size_t>> floydMat = this->player.mapAll(index, numPlanets,
        galaxy.getGraph().getMatAd(), iterations);
    high_resolution_clock::time_point end = high_resolution_clock::now();
    elapsed = end - start;

    log.register_noAttack(iterations,player.units[index]->getName(), elapsed.count());
    
    vector<bool>& visited = this->player.getPVisited();
    vector<bool>& mapped = this->player.getPMapped();
    for (int i = 0; i < visited.size(); i++){
        if(visited[i]){
            mapped[i]= true;
        }
    }

    return floydMat;
}

void Model::probarDijkstra(){
    Galaxy& galaxy = galaxies[actualGalaxy];
    size_t numPlanets = galaxy.getGalaxySize();
    vector<bool>& visited = this->player.getPVisited();
    size_t iterations = 0;
    cout<< "Prueba Dijkstra "<<endl;
    size_t distancia = dijkstra(numPlanets, galaxy.getGraph().getListAd(), 0, 7, visited, iterations);
    cout<< " "<< distancia <<" "<<endl;
}

void Model::probarFloyd(){

    Galaxy& galaxy = galaxies[actualGalaxy];
    size_t numPlanets = galaxy.getGalaxySize();
    vector<bool>& visited = this->player.getPVisited();
    size_t iterations = 0;
    vector<vector<size_t>> matAd = floydWarshall( numPlanets,galaxy.getGraph().getMatAd(), visited, iterations);
    cout<< " Prueba de floyd"<< endl;
    cout << "Matriz de adyacencia:\n";
    for (size_t i = 0; i < numPlanets; ++i) {
        for (size_t j = 0; j < numPlanets; ++j) {
            if (matAd[i][j] == INVALID) {
                cout << "INVALID ";
            } else {
                cout << matAd[i][j] << " ";
            }
        }
        cout << endl;
    }
 
}

void Model:: probarBFS(){
    Galaxy& galaxy = galaxies[actualGalaxy];
    size_t numPlanets = galaxy.getGalaxySize();
    size_t iterations = 0;
    vector<bool>& visited = this->player.getPVisited();
    cout<<endl<<"Prueba BFS"<<endl;
    for(size_t i = 0; i < numPlanets; ++i){
        vector<size_t> prueba = bfs_neighbors(visited, galaxy.getGraph().getListAd(), i, iterations);
        for (size_t j = 0; j < prueba.size(); j++){
            cout<<" "<< prueba[j] <<" ";
        }
        cout<<endl;
    }
}

void Model:: probarDFS(){
    Galaxy& galaxy = galaxies[actualGalaxy];
    size_t numPlanets = galaxy.getGalaxySize();
    vector<bool>& visited = this->player.getPVisited();
    size_t iterations = 0;
    cout<<endl<<"Prueba DFS"<<endl;
    for(size_t i = 0; i < numPlanets; ++i){
        vector<size_t> prueba = dfs_set_depth(visited, galaxy.getGraph().getListAd(), 0, iterations);
        for (size_t j = 0; j < prueba.size(); j++){
            cout<<" "<< prueba[j] <<" ";
        }
        cout<<endl;
        iterations = 0;
    }
}

void Model::printGalaxy() {
    galaxies[this->actualGalaxy].printer();
}

const Galaxy& Model::getGalaxy(int index) const {
    return galaxies[index];
}

void Model::nextGalaxy(){
    actualGalaxy = actualGalaxy + 1;
}

size_t Model:: getActualGalaxy() const{
    return this->actualGalaxy;
}

vector<Galaxy> Model::getGalaxies() {
    return galaxies;
}

vector<vector<size_t>> Model:: getMatAd(){
    Galaxy& galaxy = galaxies[actualGalaxy];
    return galaxy.getGraph().getMatAd();
}

int Model::increaseEterium(int eterium){
    player.addEterium(eterium);
    return player.getEterium();
}

bool Model:: notFinished(){
    bool notFinished = true;
    if(getActualGalaxy() == (galaxies.size()-1))
        notFinished = false;
    return notFinished;
}