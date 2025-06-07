#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <random>
#include <filesystem>

#include <FL/Fl.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>
#include <Fl/Fl_Box.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/fl_draw.H>
#include <FL/fl_ask.H>


#include "Model.h"


using namespace std;
namespace fs = filesystem;

class View {
private:
    Model& model;
    vector<Fl_Image*> maps;
    unordered_map<string,Fl_Image*> icons;
    unordered_map<string,Fl_Image*> ships;
    vector<Fl_Image*> bosses;


    static constexpr int MAPSIZEX     = 1280;
    static constexpr int MAPSIZEY     = 720;
    static constexpr int MAPX         = 0;
    static constexpr int MAPY         = 0;

    static constexpr int SHIPSIZEX    = 70;
    static constexpr int SHIPSIZEY    = 60;
    static constexpr int SHIPX        = 400;
    static constexpr int SHIPY        = 640;
    static constexpr int SHIPSPACE    = 100;

    static constexpr int BOSSSIZEX    = 100;
    static constexpr int BOSSSIZEY    = 100;
    static constexpr int BOSSX        = 600;
    static constexpr int BOSSY        = 200;

    static constexpr int MENUSIZEX    = 50;
    static constexpr int MENUSIZEY    = 50;
    static constexpr int MENUX        = 20;
    static constexpr int MENUY        = 650;
    static constexpr int MENUSPACE    = 52;

    static constexpr int INFOSIZEX    = 0;
    static constexpr int INFOSIZEY    = 0;
    static constexpr int INFOX        = 280;
    static constexpr int INFOY        = 635;

    static constexpr int PLANETNUMBER = 20;
    static constexpr int PLANETSIZEX  = 50;
    static constexpr int PLANETSIZEY  = 50;
    static constexpr int PLANETX      = 50;
    static constexpr int PLANETY      = 100;
    static constexpr int PLANETSPACING = 60;

    
    static constexpr int number_of_maps   = 11;
    static constexpr int number_of_bosses = 5;


    void load_maps();
    void load_ships();
    void load_bosses();
    void load_menus();
    void load_planets();

public:
    View(Model& model);
    ~View();

    void initialize();

    void show();
    void hide();

    int random_map_number();
    void random_map_generation();

    int random_boss_number();
    void random_boss_generation();


    bool aborted() const { return escape; }
    bool winCondition() const { return conquered; }

    bool attacking;
    bool exploring;
    bool mapping;
    bool shopping;
    bool escape;
    bool conquered;

    Fl_Window* frame;
    Fl_Box* background;

    Fl_Button* interceptor;
    Fl_Button* barracuda;
    Fl_Button* saboteur;
    Fl_Button* annihilator;
    Fl_Button* battleray;

    Fl_Button* boss;

    Fl_Button* logout;
    Fl_Button* attack;
    Fl_Button* explore;
    Fl_Button* mapper;
    Fl_Button* shop;
    Fl_Button* money;

    Fl_Box* info;

    std::vector<Fl_Button*> planets;
};

