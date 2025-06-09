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

    static constexpr int GATESIZEX    = 90;
    static constexpr int GATESIZEY    = 100;
    static constexpr int GATEX        = 1180;
    static constexpr int GATEY        = 200;

    static constexpr int SHIPSIZEX    = 70;
    static constexpr int SHIPSIZEY    = 60;
    static constexpr int SHIPX        = 250;
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
    static constexpr int MENUSPACE    = 1190;

    static constexpr int PLANETNUMBER = 20;
    static constexpr int PLANETSIZEX  = 50;
    static constexpr int PLANETSIZEY  = 50;
    static constexpr int PLANETX      = 50;
    static constexpr int PLANETY      = 100;
    static constexpr int PLANETSPACING = 60;

    static constexpr int number_of_maps   = 11;
    static constexpr int number_of_bosses = 5;

    static constexpr int INFOSIZEX    = 0;
    static constexpr int INFOSIZEY    = 0;
    static constexpr int INFOX        = 5;
    static constexpr int INFOY        = 10;

    static constexpr int ETERIUMSIZEX    = 0;
    static constexpr int ETERIUMSIZEY    = 0;
    static constexpr int ETERIUMX        = 1190;
    static constexpr int ETERIUMY        = 630;

    static constexpr int MINEINFOX        = 540;
    static constexpr int MINEINFOY        = 10;

    void load_maps();
    void load_ships();
    void load_bosses();
    void load_menus();
    void load_planets();




    class LineDrawer : public Fl_Widget {
    private:
        struct Line {
            int x1, y1, x2, y2;
            Fl_Color color;
        };

        std::vector<Line> lines;

    public:
        LineDrawer(int X, int Y, int W, int H)
            : Fl_Widget(X, Y, W, H) {}

        void add_line(int x1, int y1, int x2, int y2, Fl_Color color = FL_WHITE){
            lines.push_back({x1, y1, x2, y2, color});
            redraw();
        }

        void clear_lines(){
            lines.clear();
            redraw();
        }

        void draw() override {
            for (const Line& line : lines){
                fl_color(line.color);
                fl_line(line.x1, line.y1, line.x2, line.y2);
            }
        }
    };

     

    class HoverButton : public Fl_Button {
        Fl_Box* label_box;
        const char* hover_text;

    public:
        HoverButton(int X, int Y, int W, int H, Fl_Box* hover_label = nullptr, const char* hover_msg = "")
            : Fl_Button(X, Y, W, H), label_box(hover_label), hover_text(hover_msg) {}

        int handle(int event) override {
            switch (event) {
                case FL_ENTER:
                    if (label_box) {
                        label_box->label(hover_text);
                        label_box->position(this->x() - 25, this->y() - 20); 
                        label_box->show();
                    }
                    return 1;

                case FL_LEAVE:
                    if (label_box) {
                        label_box->hide();
                    }
                    return 1;

                default:
                    return Fl_Button::handle(event);
            }
        }
    };





public:
    View(Model& model);
    ~View();

    LineDrawer* lineDrawer;

    void initialize();

    void show();
    void hide();

    int random_map_number();
    void random_map_generation();

    int random_boss_number();
    void random_boss_generation();

    void planet_info();

    bool aborted() const { return escape; }
    bool winCondition() const { return conquered; }

    void nextGalaxy();

    void newBoss();

    bool attacking;
    bool exploring;
    bool mapping;
    bool shopping;
    bool escape;
    bool conquered;

    Fl_Window* frame;
    Fl_Box* background;

    Fl_Button* gate;

    Fl_Button* Reflector;
    Fl_Button* Agatus;
    Fl_Button* Charopos;
    Fl_Button* Convict;
    Fl_Button* Impulse;
    Fl_Button* Stiger;
    Fl_Button* Streuner;
    Fl_Button* Artemis;

    Fl_Button* boss;

    Fl_Button* logout;
    HoverButton* money;

    Fl_Box* info;
    Fl_Box* eterium;
    Fl_Box* mine_count;
    Fl_Box* boss_life;

    Fl_Box* info_visited;
    Fl_Box* info_mapped;
    Fl_Box* info_eterium;
    Fl_Box* info_ship;

    vector<Fl_Button*> planets;

    void updateBossLife(int bossLife);
    // void bossDead();
    // void showPortalButton();
};
