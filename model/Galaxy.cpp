#include "Galaxy.h"

Galaxy::Galaxy() {}

void Galaxy::chartist() {

    planetarium = vector<vector<Planet*>> (latitude, vector<Planet*>(longitude, nullptr)) ;


}

void Galaxy::printer() {
    
    for (int i = 0; i < planetarium.size(); ++i) {
        for (int j = 0; j < planetarium[i].size(); ++j) {
            if (planetarium[i][j] != nullptr) {
                std::cout << "1 ";
            } else {
                std::cout << "0 ";
            }
        }
        std::cout << "\n";
    }
    
}

Galaxy::~Galaxy() {

}