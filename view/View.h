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
namespace fs = std::filesystem;

class View {

private:

    Model model;

    Fl_Window* frame;
    Fl_Box* background;

    vector<Fl_Image*> maps;
    unordered_map<string, Fl_Image*> icons;
    unordered_map<string, Fl_Image*> ships;

    vector<Fl_Image*> bosses;
    Fl_Button* boss;

    vector<Fl_Button*> planets;

    Fl_Button* logout;
    Fl_Button* attack;
    Fl_Button* explore;
    Fl_Button* mapper;
    Fl_Button* shop;
    Fl_Button* money;


    Fl_Button* interceptor;
    Fl_Button* barracuda;
    Fl_Button* saboteur;
    Fl_Button* annihilator;
    Fl_Button* battleray;

    Fl_Box* info;

    bool conquered;
    bool escape;

    bool attacking;
    bool exploring;
    bool mapping;
    bool shopping;


    static constexpr int number_of_maps = 11;
    static constexpr int number_of_bosses = 5;

public:
    View();
    ~View();

    void run(Model& model);

    void show();
    void hide();

    bool exterminatused();
    static void exterminatus(Fl_Widget* w, void* user_data);

    int random_map_number();
    int random_boss_number();
    void load_maps();
    void random_map_generation();

    void load_ui_elements();

    void load_ships();
    static void manage_ship_click(Fl_Widget* w, void* user_data);

    void load_bosses();
    void random_boss_generation();
    static void manage_boss_click(Fl_Widget* w, void* user_data);


    void load_menus();

    static void manage_logout_click(Fl_Widget* w, void* user_data);
    static void manage_attack_click(Fl_Widget* w, void* user_data);
    static void manage_explore_click(Fl_Widget* w, void* user_data);
    static void manage_mapper_click(Fl_Widget* w, void* user_data);
    static void manage_shop_click(Fl_Widget* w, void* user_data);
    static void manage_money_click(Fl_Widget* w, void* user_data);

    bool abort();

    void attack_mode();
    void exploration_mode();
    void mapping_mode();
    void shopping_mode();
    void reset_modes();

    void load_planets();
    void manage_planets();

};