#include "Model.h"

//#include "Galaxy.h"

#include <iostream>

using namespace std;

int main() {
    Model model;

    string test = "test.csv";
    model.loadGalaxy(test);
    model.printGalaxy();

    // Galaxy ultramar("venus", "earth", "mars");
    // ultramar.chartist();

    // ultramar.printer();

}

