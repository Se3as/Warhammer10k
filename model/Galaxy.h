#pragma once

#include <iostream>
#include <vector>


using namespace std;


class galaxy {

private:
vector<vector<int*>> constelation;

static constexpr int latitude = 10;
static constexpr int longitude = 10;


public:
    galaxy();
    ~galaxy();


    void chartist();

    void link_probability();


};