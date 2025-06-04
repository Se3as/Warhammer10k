#include "Graph.h"

Graph::Graph(size_t numPlanets) : numPlanets(numPlanets) {
    matAd = vector<vector<size_t>>(numPlanets, vector<size_t>(numPlanets, INVALID));
    listAd = vector<vector<Edge>>(numPlanets);
}

vector<vector<Edge>> Graph:: getListAd(){
    return listAd;
}
vector<vector<size_t>> Graph:: getMatAd(){
    return matAd;
}

// Para ue no se vea cargado origin: ID planeta origen destination: ID planeta destino
void Graph::addCon(size_t origin, size_t destination, size_t distance) {
    
    matAd[origin][destination] = distance;
    matAd[destination][origin] = distance;

    listAd[origin].push_back({destination, distance});
    listAd[destination].push_back({origin, distance});
}
// Para ue no se vea cargado origin: ID planeta origen destination: ID planeta destino
void Graph::deleteCon(size_t origin, size_t destination) {

    matAd[origin][destination] = INVALID;
    matAd[destination][origin] = INVALID;

    for (size_t i = 0; i < listAd[origin].size(); ++i) {
        if (listAd[origin][i].id == destination) {
            listAd[origin].erase(listAd[origin].begin() + i);
            break;
        }
    }

    for (size_t i = 0; i < listAd[destination].size(); ++i) {
        if (listAd[destination][i].id == origin) {
            listAd[destination].erase(listAd[destination].begin() + i);
            break;
        }
    }
}
bool Graph:: hasEdge(size_t origin, size_t destination) {
      if (matAd[origin][destination]!= INVALID){
        return true;
      }
}

void Graph::printMat() {
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

void Graph::printList() {
    cout << "Lista de adyacencia:\n";
    for (size_t i = 0; i < numPlanets; ++i) {
        cout << i << ": ";
        for (Edge neighbor : listAd[i]) {
            cout << "(" << neighbor.id << ", " << neighbor.dist << ") ";
        }
        cout << endl;
    }
}

