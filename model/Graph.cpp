#include "Graph.h"

Graph::Graph(int numPlanetas) : numPlanetas(numPlanetas) {
    matAd = vector<vector<int>>(numPlanetas, vector<int>(numPlanetas, INVALID));
    listAd = vector<vector<pair<int, int>>>(numPlanetas);
}

// Para ue no se vea cargado iPO: ID planeta origen iPD: ID planeta destino
void Graph::addCon(int iPO, int iPD, int distancia) {
    
    matAd[iPO][iPD] = distancia;
    matAd[iPD][iPO] = distancia;

    listAd[iPO].push_back({iPD, distancia});
    listAd[iPD].push_back({iPO, distancia});
}
// Para ue no se vea cargado iPO: ID planeta origen iPD: ID planeta destino
void Graph::deleteCon(int iPO, int iPD) {

    matAd[iPO][iPD] = INVALID;
    matAd[iPD][iPO] = INVALID;

    for (int i = 0; i < listAd[iPO].size(); ++i) {
        if (listAd[iPO][i].first == iPD) {
            listAd[iPO].erase(listAd[iPO].begin() + i);
            break;
        }
    }

    for (int i = 0; i < listAd[iPD].size(); ++i) {
        if (listAd[iPD][i].first == iPO) {
            listAd[iPD].erase(listAd[iPD].begin() + i);
            break;
        }
    }
}

void Graph::printMat() {
    cout << "Matriz de adyacencia:\n";
    for (int i = 0; i < numPlanetas; ++i) {
        for (int j = 0; j < numPlanetas; ++j) {
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
    for (int i = 0; i < numPlanetas; ++i) {
        cout << i << ": ";
        for (std::pair<int, int> vecino : listAd[i]) {
            cout << "(" << vecino.first << ", " << vecino.second << ") ";
        }
        cout << endl;
    }
}

