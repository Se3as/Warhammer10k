#pragma once

#include <iostream>
#include <string>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
using namespace std;



class SpaceUnit {
private:

    string name;
    int price;

public:
    SpaceUnit(string n, int p): name(n), price(p) {}
    virtual ~SpaceUnit() {}

        
    int getPrice();
    void setPrice(int p);
    string getName();
    void setName(string n);

};