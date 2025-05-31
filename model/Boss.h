#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Boss {

private:

    string name;

    int life_points;

public:
    Boss();
    ~Boss();

    string getBossID();

    void setBossHP(int hp);

    int getBossHP() const;
    
};