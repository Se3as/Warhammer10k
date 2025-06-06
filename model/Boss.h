#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Boss {

private:

    string name;

    size_t life_points;

public:
    Boss();
    ~Boss(){}

    string getBossID();

    void setBossHP(size_t hp);

    size_t getBossHP() const;

    size_t receiveDamage(size_t damage);
    
};