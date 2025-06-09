#include "View.h"
#include <FL/fl_draw.H>
#include <iostream>

View::View(Model& model): model(model), attacking(false),exploring(false), mapping(false),
    shopping(false), escape(false), conquered(false), frame(nullptr), background(nullptr),
    Reflector(nullptr), Agatus(nullptr), Charopos(nullptr), Convict(nullptr),
    Impulse(nullptr), Stiger(nullptr), Streuner(nullptr), Artemis(nullptr), boss(nullptr), logout(nullptr), money(nullptr), info(nullptr), boss_life(nullptr){}


View::~View() {
    delete frame;
}

void View::show(){
    frame->show();
}

void View::hide(){
    frame->hide();
}

void View::initialize() {
    load_maps();
    load_menus();
    load_ships();
    load_bosses();
    load_planets();
}

//GENERA UN NUMERO ALEATORIO PARA RANDOMIZAR LOS MAPAS
int View::random_map_number(){
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, number_of_maps - 1);
    return distrib(gen);
}

//REFREZCA Y ALEATORIZA EL MAPA
void View::random_map_generation(){
    background->image(maps[random_map_number()]);
}

//GENERA UN NUMERO RANDOM PARA EL BOSS
int View::random_boss_number(){
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, number_of_bosses - 1);
    return distrib(gen);
}

//REFREZCA EL BOSS
void View::random_boss_generation(){
    boss->image(bosses[random_boss_number()]);
}
// CARGA TODOS LOS POSIBLES MAPAS Y GENERA EL PRIMER MAPA
void View::load_maps() {

    const string map_catalog = "assets/gfx/maps";

    for(const auto& bookmark : fs::directory_iterator(map_catalog)){
        if (bookmark.path().extension() == ".png") {
            string image = bookmark.path().string();

            Fl_PNG_Image* starfield_temp = new Fl_PNG_Image(image.c_str());
            Fl_Image* starfield = starfield_temp->copy(MAPSIZEX, MAPSIZEY);
            delete starfield_temp;

            maps.push_back(starfield);
        }
    }

    frame = new Fl_Window(MAPSIZEX, MAPSIZEY, "Warhammer 10k");
    background = new Fl_Box(MAPX, MAPY, MAPSIZEX, MAPSIZEY);
    background->image(maps[random_map_number()]);

    lineDrawer = new LineDrawer(0, 0, MAPSIZEX, MAPSIZEY); 
    frame->add(lineDrawer); 


}

//CARGA LAS NAVES
void View::load_ships(){
    const string ship_catalog = "assets/gfx/ships";

    for(const auto& bookmark : fs::directory_iterator(ship_catalog)){
        if (bookmark.path().extension() == ".png") {
            string image = bookmark.path().string();

            string ship_id = bookmark.path().stem().string();

            Fl_PNG_Image* ship_temp = new Fl_PNG_Image(image.c_str());
            Fl_Image* ship = ship_temp->copy(SHIPSIZEX, SHIPSIZEY);
            delete ship_temp;

            ships[ship_id] = ship;
        }
    }

    Reflector = new HoverButton(SHIPX, SHIPY, SHIPSIZEX, SHIPSIZEY, info_ship, " Pathfinder");
    Reflector->box(FL_NO_BOX);
    Reflector->image(ships["Reflector"]);
    Reflector->clear_visible_focus();

    Agatus = new HoverButton((SHIPX + SHIPSPACE), SHIPY, SHIPSIZEX, SHIPSIZEY, info_ship, "StarMapper");
    Agatus->box(FL_NO_BOX);
    Agatus->image(ships["Agatus"]);
    Agatus->clear_visible_focus();

    Convict = new HoverButton((SHIPX + (SHIPSPACE * 2)), SHIPY, SHIPSIZEX, SHIPSIZEY, info_ship, "Asalto Ligero");
    Convict->box(FL_NO_BOX);
    Convict->image(ships["Convict"]);
    Convict->clear_visible_focus();

    Charopos = new HoverButton((SHIPX + (SHIPSPACE * 3)), SHIPY, SHIPSIZEX, SHIPSIZEY, info_ship, "Asalto Medio");
    Charopos->box(FL_NO_BOX);
    Charopos->image(ships["Charopos"]);
    Charopos->clear_visible_focus();

    Impulse = new HoverButton((SHIPX + (SHIPSPACE * 4)), SHIPY, SHIPSIZEX, SHIPSIZEY, info_ship, "Asalto Pesado");
    Impulse->box(FL_NO_BOX);
    Impulse->image(ships["Impulse"]);
    Impulse->clear_visible_focus();

    Stiger= new HoverButton((SHIPX + (SHIPSPACE * 5)), SHIPY, SHIPSIZEX, SHIPSIZEY, info_ship, "Asalto Pesado+");
    Stiger->box(FL_NO_BOX);
    Stiger->image(ships["Stiger"]);
    Stiger->clear_visible_focus();

    Streuner= new HoverButton((SHIPX + (SHIPSPACE * 6)), SHIPY, SHIPSIZEX, SHIPSIZEY, info_ship, "RapidSight");
    Streuner->box(FL_NO_BOX);
    Streuner->image(ships["Streuner"]);
    Streuner->clear_visible_focus();

    Artemis= new HoverButton((SHIPX + (SHIPSPACE * 7)), SHIPY, SHIPSIZEX, SHIPSIZEY, info_ship, "DeepProbe");
    Artemis->box(FL_NO_BOX);
    Artemis->image(ships["Artemis"]);
    Artemis->clear_visible_focus();
}

//CARGA LOS BOSSES
void View::load_bosses(){

    const string boss_catalog = "assets/gfx/bosses";

    for(const auto& bookmark : fs::directory_iterator(boss_catalog)){
        if (bookmark.path().extension() == ".png") {
            string image = bookmark.path().string();

            Fl_PNG_Image* boss_temp = new Fl_PNG_Image(image.c_str());
            Fl_Image* boss = boss_temp->copy(BOSSSIZEX, BOSSSIZEY);
            delete boss_temp;

            bosses.push_back(boss);
        }
    }
    newBoss();
}


void View::newBoss(){
    boss = new Fl_Button(BOSSX, BOSSY, BOSSSIZEX, BOSSSIZEY);
    boss->box(FL_NO_BOX);
    boss->image(bosses[random_boss_number()]);
}


// //CARGA LOS BOTONES MENUS
void View::load_menus(){

    const string menu_catalog = "assets/gfx/icons";

    for(const auto& bookmark : fs::directory_iterator(menu_catalog)){
        if (bookmark.path().extension() == ".png") {
            string image = bookmark.path().string();

            string menu_id = bookmark.path().stem().string();

            Fl_PNG_Image* menu_temp = new Fl_PNG_Image(image.c_str());
            Fl_Image* menu = menu_temp->copy(MENUSIZEX, MENUSIZEY);
            delete menu_temp;

            icons[menu_id] = menu;
        }
    }

    info_eterium = new Fl_Box(ETERIUMX, ETERIUMY, ETERIUMSIZEX, ETERIUMSIZEY);
    info_eterium->labelcolor(fl_rgb_color(85, 132, 156));
    info_eterium->align(FL_ALIGN_RIGHT);
    info_eterium->labelsize(18);
    info_eterium->hide();

    info_ship = new Fl_Box(MENUX, MENUY + 30, INFOSIZEY, INFOSIZEX);
    info_ship->labelcolor(fl_rgb_color(85, 132, 156));
    info_ship->align(FL_ALIGN_RIGHT);
    info_ship->labelsize(18);
    info_ship->hide();

    info_visited = new Fl_Box(MENUX, MENUY + 30, INFOSIZEY, INFOSIZEX, "Visitado");
    info_visited->labelcolor(fl_rgb_color(85, 132, 156));
    info_visited->align(FL_ALIGN_RIGHT);
    info_visited->labelsize(18);
    info_visited->hide();

    info_mapped = new Fl_Box(MENUX, MENUY + 30, INFOSIZEY, INFOSIZEX, "Mapeado");
    info_mapped->labelcolor(fl_rgb_color(85, 132, 156));
    info_mapped->align(FL_ALIGN_RIGHT);
    info_mapped->labelsize(18);
    info_mapped->hide();


    //LABEL PARA EL ETERIUM
    eterium = new Fl_Box((MENUX + (MENUSPACE - 50)), MENUY + 30, INFOSIZEY, INFOSIZEX, "0");
    eterium->labelcolor(fl_rgb_color(85, 132, 156));
    eterium->align(FL_ALIGN_RIGHT);
    eterium->labelsize(18);
    eterium->hide();

    //LABEL PARA FEEDBACK
    info = new Fl_Box(INFOX, INFOY, INFOSIZEX, INFOSIZEY, "PLAYER PLAYING");
    info->labelcolor(fl_rgb_color(85, 132, 156));
    info->align(FL_ALIGN_RIGHT);
    info->labelsize(18);
    info->hide();

    //LABEL PARA CONTADOR DE MINAS
    mine_count = new Fl_Box(MINEINFOX, MINEINFOY, INFOSIZEX, INFOSIZEY, "MINES ACQUIRED: ");
    mine_count->labelcolor(fl_rgb_color(85, 132, 156));
    mine_count->align(FL_ALIGN_RIGHT);
    mine_count->labelsize(18);

    //LABEL PARA LA VIDA DEL BOOS
    boss_life = new Fl_Box(INFOX, INFOY, INFOSIZEX, INFOSIZEY, "BOSS LIFE: ");
    boss_life->labelcolor(fl_rgb_color(85, 132, 156));
    boss_life->align(FL_ALIGN_RIGHT);
    boss_life->labelsize(18);
    
    logout = new Fl_Button(MENUX, MENUY, MENUSIZEX, MENUSIZEY);
    logout->box(FL_NO_BOX);
    logout->image(icons["DO_logout"]);
    logout->clear_visible_focus();

    money = new HoverButton((MENUX + (MENUSPACE)), MENUY, MENUSIZEX, MENUSIZEY, info_eterium, "Excavador");
    money->box(FL_NO_BOX);
    money->image(icons["Eterium"]);
    money->clear_visible_focus();
    
    
    Fl_PNG_Image* gate_temp = new Fl_PNG_Image("assets/gfx/icons/kappagate.png");
    Fl_Image* gate_icon = gate_temp->copy(GATESIZEX, GATESIZEY);
    delete gate_temp;
    gate = new Fl_Button(GATEX, GATEY, GATESIZEX, GATESIZEY);
    gate->box(FL_NO_BOX);
    gate->image(gate_icon);
}


void View::load_planets() {

    const vector<Galaxy>& galaxies = model.getGalaxies();
    const Galaxy& galaxy = galaxies[model.getActualGalaxy()];   
    const vector<Planet*>& planetarium = galaxy.getPlanets();



    for (size_t p = 0; p < planetarium.size(); ++p) {
        const Planet* pl = planetarium[p];
        int x = pl->getPosX();
        int y = pl->getPosY();

        Fl_Button* btn = new Fl_Button(x, y, PLANETSIZEX, PLANETSIZEY);
        btn->box(FL_NO_BOX);
        frame->add(btn);

        if(p < planetarium.size() - 1){

            const Planet* pl2 = planetarium[p + 1];
            int x2 = pl2->getPosX();
            int y2 = pl2->getPosY();

            //lineDrawer->add_line(x, y, x2, y2, FL_WHITE);
        }

        if(p == (planetarium.size() - 1)){
            btn->image(icons["acm01"]);
            boss->position(x, y - 105);
            boss_life->position(x + 25, y - 130);


        } else {
            btn->image(icons["planet"]);

        }
        planets.push_back(btn);
    }

}

void View::nextGalaxy(){

    for (Fl_Button* btn : planets) {
        frame->remove(btn); 
        delete btn;       
    }
    planets.clear();  
    

    lineDrawer->clear_lines();

    model.nextGalaxy();

    load_planets();

    random_map_generation();
    random_boss_generation();

}

// //PONE LA LABEL DE FEEDBACK DEBAJO DEL PLANETA
// void View::planet_info(){
//     const vector<Galaxy>& galaxies = model.getGalaxies();
//     const Galaxy& galaxy = galaxies[model.getActualGalaxy()];   
//     const vector<Planet*>& planetarium = galaxy.getPlanets();

    

// }

// Update the boss life after the player attacks the boss
void View::updateBossLife(int bossLife) {
    // boss_life->label(std::to_string(bossLife).c_str());
}

// Update the eterium after the player collects or spends it
void View::updateEterium(int eterium) {
    // money->label(std::to_string(eterium).c_str());
}
