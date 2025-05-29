#include "Model.h"

#include <iostream>

using namespace std;

int main() {

    Model model;

    string test = "test.csv";
    model.loadGalaxy(test);
    model.printGalaxy();

}

