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
    load_ships();
    load_bosses();
    load_menus();
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

// void View::draw_line_between(int x1, int y1, int x2, int y2, Fl_Color color) {
//     lineDrawer->set_points(x1, y1, x2, y2, color);
// }


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

    Reflector = new Fl_Button(SHIPX, SHIPY, SHIPSIZEX, SHIPSIZEY);
    Reflector->box(FL_NO_BOX);
    Reflector->image(ships["Reflector"]);
    // Reflector->callback(manage_ship_click, this);

    Agatus = new Fl_Button((SHIPX + SHIPSPACE), SHIPY, SHIPSIZEX, SHIPSIZEY);
    Agatus->box(FL_NO_BOX);
    Agatus->image(ships["Agatus"]);
    // Agatus->callback(manage_ship_click, this);

    Convict = new Fl_Button((SHIPX + (SHIPSPACE * 2)), SHIPY, SHIPSIZEX, SHIPSIZEY);
    Convict->box(FL_NO_BOX);
    Convict->image(ships["Convict"]);
    // Convict->callback(manage_ship_click, this);

    Charopos = new Fl_Button((SHIPX + (SHIPSPACE * 3)), SHIPY, SHIPSIZEX, SHIPSIZEY);
    Charopos->box(FL_NO_BOX);
    Charopos->image(ships["Charopos"]);
    // Charopos->callback(manage_ship_click, this);

    Impulse = new Fl_Button((SHIPX + (SHIPSPACE * 4)), SHIPY, SHIPSIZEX, SHIPSIZEY);
    Impulse->box(FL_NO_BOX);
    Impulse->image(ships["Impulse"]);
    // Impulse->callback(manage_ship_click, this);

    Stiger= new Fl_Button((SHIPX + (SHIPSPACE * 5)), SHIPY, SHIPSIZEX, SHIPSIZEY);
    Stiger->box(FL_NO_BOX);
    Stiger->image(ships["Stiger"]);
    // Stiger->callback(manage_ship_click, this);

    Streuner= new Fl_Button((SHIPX + (SHIPSPACE * 6)), SHIPY, SHIPSIZEX, SHIPSIZEY);
    Streuner->box(FL_NO_BOX);
    Streuner->image(ships["Streuner"]);
    // Streuner->callback(manage_ship_click, this);

    Artemis= new Fl_Button((SHIPX + (SHIPSPACE * 7)), SHIPY, SHIPSIZEX, SHIPSIZEY);
    Artemis->box(FL_NO_BOX);
    Artemis->image(ships["Artemis"]);
    // Artemis->callback(manage_ship_click, this);

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

    boss = new Fl_Button(BOSSX, BOSSY, BOSSSIZEX, BOSSSIZEY);
    boss->box(FL_NO_BOX);
    boss->image(bosses[random_boss_number()]);
    // boss->callback(manage_boss_click, this);
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

    //LABEL PARA EL ETERIUM
    eterium = new Fl_Box(ETERIUMX, ETERIUMY, ETERIUMSIZEX, ETERIUMSIZEY);
    eterium->labelcolor(fl_rgb_color(85, 132, 156));
    eterium->align(FL_ALIGN_RIGHT);
    eterium->labelsize(18);
    //eterium->hide();

    //LABEL PARA FEEDBACK
    info = new Fl_Box(INFOX, INFOY, INFOSIZEX, INFOSIZEY, "PLAYER PLAYING");
    info->labelcolor(fl_rgb_color(85, 132, 156));
    info->align(FL_ALIGN_RIGHT);
    info->labelsize(18);
    //info->hide();

    //LABEL PARA PLANETA VISITADO
    feedblack = new Fl_Box(INFOX, INFOY, INFOSIZEX, INFOSIZEY, "VISITED");
    feedblack->labelcolor(fl_rgb_color(85, 132, 156));
    feedblack->align(FL_ALIGN_RIGHT);
    feedblack->labelsize(18);
    //feedblack->hide();

    //LABEL PARA CONTADOR DE MINAS
    mine_count = new Fl_Box(MINEINFOX, MINEINFOY, INFOSIZEX, INFOSIZEY, "MINES ACQUIRED: ");
    mine_count->labelcolor(fl_rgb_color(85, 132, 156));
    mine_count->align(FL_ALIGN_RIGHT);
    mine_count->labelsize(18);
    //mine_count->hide();

    //LABEL PARA LA VIDA DEL BOOS
    boss_life = new Fl_Box(INFOX, INFOY, INFOSIZEX, INFOSIZEY, "BOSS LIFE: ");
    boss_life->labelcolor(fl_rgb_color(85, 132, 156));
    boss_life->align(FL_ALIGN_RIGHT);
    boss_life->labelsize(18);
    boss_life->hide();
    
    logout = new Fl_Button(MENUX, MENUY, MENUSIZEX, MENUSIZEY);
    logout->box(FL_NO_BOX);
    logout->image(icons["DO_logout"]);
    logout->clear_visible_focus();
    // logout->callback(manage_logout_click, this);

    // attack = new Fl_Button((MENUX + MENUSPACE), MENUY, MENUSIZEX, MENUSIZEY);
    // attack->box(FL_FLAT_BOX);
    // attack->color(FL_WHITE);
    // attack->image(icons["DO_attack"]);
    // attack->clear_visible_focus();
    // // attack->callback(manage_logout_click, this);

    // explore = new Fl_Button((MENUX + (MENUSPACE * 2)), MENUY, MENUSIZEX, MENUSIZEY);
    // explore->box(FL_FLAT_BOX);
    // explore->color(FL_WHITE);
    // explore->image(icons["DO_explore"]);
    // explore->clear_visible_focus();
    // // explore->callback(manage_logout_click, this);

    // mapper = new Fl_Button((MENUX + (MENUSPACE * 3)), MENUY, MENUSIZEX, MENUSIZEY);
    // mapper->box(FL_FLAT_BOX);
    // mapper->color(FL_WHITE);
    // mapper->image(icons["DO_map"]);
    // mapper->clear_visible_focus();
    // // mapper->callback(manage_logout_click, this);

    // shop = new Fl_Button((MENUX + (MENUSPACE * 4)), MENUY, MENUSIZEX, MENUSIZEY);
    // shop->box(FL_FLAT_BOX);
    // shop->color(FL_WHITE);
    // shop->image(icons["DO_shop"]);
    // shop->clear_visible_focus();
    // // shop->callback(manage_logout_click, this);

    money = new HoverButton((MENUX + (MENUSPACE)), MENUY, MENUSIZEX, MENUSIZEY, "Eterium label" , eterium, "Eterium");
    money->box(FL_NO_BOX);
    money->image(icons["Eterium"]);
    money->clear_visible_focus();
    // money->callback(manage_money_click, this);

    Fl_PNG_Image* gate_temp = new Fl_PNG_Image("assets/gfx/icons/kappagate.png");
    Fl_Image* gate_icon = gate_temp->copy(GATESIZEX, GATESIZEY);
    delete gate_temp;
    gate = new Fl_Button(GATEX, GATEY, GATESIZEX, GATESIZEY);
    gate->box(FL_NO_BOX);
    gate->image(gate_icon);
    //gate->callback();

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

        if(p < planetarium.size() - 1){

            const Planet* pl2 = planetarium[p + 1];
            int x2 = pl2->getPosX();
            int y2 = pl2->getPosY();

            //ejemplo de linea de otro color
            if(p == 1){
                lineDrawer->add_line(x, y, x2, y2, FL_YELLOW);
            } else {
                lineDrawer->add_line(x, y, x2, y2, FL_WHITE);
            }


        }

        if(p == (planetarium.size() - 1)){
            btn->image(icons["acm01"]);
            boss->position(x, y - 105);
            feedblack->position(x - 10, y + 70);  //<--- cambiar a planet info


        } else {
            btn->image(icons["planet"]);

        }
        planets.push_back(btn);
    }

}

void View::nextGalaxy(){
    random_map_generation();
    random_boss_generation();

    //ESTO DBERIA TENER OTRO LOAD PLANETS


}

//PONE LA LABEL DE FEEDBACK DEBAJO DEL PLANETA
void View::planet_info(){
    const vector<Galaxy>& galaxies = model.getGalaxies();
    const Galaxy& galaxy = galaxies[model.getActualGalaxy()];   
    const vector<Planet*>& planetarium = galaxy.getPlanets();

    

}