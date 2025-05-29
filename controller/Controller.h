#pragma once

#include <iostream>
//#include <galaxy.h>
//#include <player.h>
//#include <view.h>
using namespace std;

class Controller {

private:
    //View View;
    //Galaxy galaxy;
    //Player player;
    
public:

    void load_galaxy();
    void explore(string explorador);
    void attack(string nave);
    void buy(string product);
    void updateEther();
    void travel(string planet);

    void run();

};