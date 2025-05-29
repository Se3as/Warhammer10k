#pragma once

#include <iostream>
#include <vector>

#include "Planet.h"

using namespace std;


class Galaxy {

private:
    vector<vector<Planet*>> planetarium;

    static constexpr int latitude = 10;
    static constexpr int longitude = 10;


public:
    Galaxy();
    ~Galaxy();

    void chartist();    //cartografo

    void link_probability();

    void printer();
};