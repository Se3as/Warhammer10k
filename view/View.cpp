#include "View.h"

#define MAPSIZEX 1280
#define MAPSIZEY 720
#define MAPX 0
#define MAPY 0

#define SHIPSIZEX 70
#define SHIPSIZEY 60
#define SHIPX 400
#define SHIPY 640
#define SHIPSPACE 100

#define BOSSSIZEX 100
#define BOSSSIZEY 100
#define BOSSX 600
#define BOSSY 200

#define MENUSIZEX 50
#define MENUSIZEY 50
#define MENUX 20
#define MENUY 650
#define MENUSPACE 52

#define INFOSIZEX 0
#define INFOSIZEY 0
#define INFOX 280
#define INFOY 635

#define PLANETNUMBER 20

#define PLANETSIZEX 50
#define PLANETSIZEY 50

#define PLANETX 50
#define PLANETY 100

#define PLANETSPACING 60

View::View(): conquered(false), escape(false), attacking(false), exploring(false), mapping(false), shopping(false){

    load_maps();
    
    load_ships();
    load_bosses();


    load_menus();


    load_planets();

}

//WIN CONDITION
bool View::exterminatused(){
    return conquered;
}

//CHANGE VALUE OF WIN CONDITION
void View::exterminatus(Fl_Widget* w, void* user_data){
    View* oribt = static_cast<View*>(user_data);
    oribt->conquered = true;
}

//GENERA UN NUMERO ALEATORIO PARA RANDOMIZAR LOS MAPAS
int View::random_map_number(){
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, number_of_maps - 1);
    return distrib(gen);
}

//GENERA UN NUMERO RANDOM PARA EL BOSS
int View::random_boss_number(){
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, number_of_bosses - 1);
    return distrib(gen);
}

void View::attack_mode(){
    if(attacking){
        attacking = false;
    } else if(!attacking){
        attacking = true;
    }
}

void View::exploration_mode(){
    if(exploring){
        exploring = false;
    } else if(!exploring){
        exploring = true;
    }
}

void View::mapping_mode(){
    if(mapping){
        mapping = false;
    } else if(!mapping){
        mapping = true;
    }
}

void View::shopping_mode(){
    if(shopping){
        shopping = false;
    } else if(!shopping){
        shopping = true;
    }
}

void View::reset_modes(){
    attacking = false;
    exploring = false;
    mapping = false;
    shopping = false;
}

//CARGA TODOS LOS POSIBLES MAPAS Y GENERA EL PRIMER MAPA
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

}

//REFREZCA Y ALEATORIZA EL MAPA
void View::random_map_generation(){
    background->image(maps[random_map_number()]);
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

    interceptor = new Fl_Button(SHIPX, SHIPY, SHIPSIZEX, SHIPSIZEY);
    interceptor->box(FL_NO_BOX);
    interceptor->image(ships["Interceptor"]);
    interceptor->callback(manage_ship_click, this);

    barracuda = new Fl_Button((SHIPX + SHIPSPACE), SHIPY, SHIPSIZEX, SHIPSIZEY);
    barracuda->box(FL_NO_BOX);
    barracuda->image(ships["Barracuda"]);
    barracuda->callback(manage_ship_click, this);

    saboteur = new Fl_Button((SHIPX + (SHIPSPACE * 2)), SHIPY, SHIPSIZEX, SHIPSIZEY);
    saboteur->box(FL_NO_BOX);
    saboteur->image(ships["Saboteur"]);
    saboteur->callback(manage_ship_click, this);

    annihilator = new Fl_Button((SHIPX + (SHIPSPACE * 3)), SHIPY, SHIPSIZEX, SHIPSIZEY);
    annihilator->box(FL_NO_BOX);
    annihilator->image(ships["Annihilator"]);
    annihilator->callback(manage_ship_click, this);

    battleray = new Fl_Button((SHIPX + (SHIPSPACE * 4)), SHIPY, SHIPSIZEX, SHIPSIZEY);
    battleray->box(FL_NO_BOX);
    battleray->image(ships["Battleray"]);
    battleray->callback(manage_ship_click, this);
}


void View::manage_ship_click(Fl_Widget* w, void* user_data){
    View* oribt = static_cast<View*>(user_data);
    
    
    //ESTA FUNCION ABE CUAL DE TODOS LOS BOTONES SE CLIKEO PARA LLAMARLA



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
    boss->callback(manage_boss_click, this);
}

//REFREZCA EL BOSS
void View::random_boss_generation(){
    boss->image(bosses[random_boss_number()]);
}


void View::manage_boss_click(Fl_Widget* w, void* user_data){

}

//CARGA LOS BOTONES MENUS
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

    //LABEL MULTIPROPOSITO
    info = new Fl_Box(INFOX, INFOY, INFOSIZEX, INFOSIZEY, "ETERIUM");
    info->labelcolor(fl_rgb_color(85, 132, 156));
    info->align(FL_ALIGN_RIGHT);
    info->labelsize(18);
    info->hide();

    logout = new Fl_Button(MENUX, MENUY, MENUSIZEX, MENUSIZEY);
    logout->box(FL_FLAT_BOX);
    logout->color(FL_WHITE);
    logout->image(icons["DO_logout"]);
    logout->clear_visible_focus();
    logout->callback(manage_logout_click, this);

    attack = new Fl_Button((MENUX + MENUSPACE), MENUY, MENUSIZEX, MENUSIZEY);
    attack->box(FL_FLAT_BOX);
    attack->color(FL_WHITE);
    attack->image(icons["DO_attack"]);
    attack->clear_visible_focus();
    attack->callback(manage_logout_click, this);

    explore = new Fl_Button((MENUX + (MENUSPACE * 2)), MENUY, MENUSIZEX, MENUSIZEY);
    explore->box(FL_FLAT_BOX);
    explore->color(FL_WHITE);
    explore->image(icons["DO_explore"]);
    explore->clear_visible_focus();
    explore->callback(manage_logout_click, this);

    mapper = new Fl_Button((MENUX + (MENUSPACE * 3)), MENUY, MENUSIZEX, MENUSIZEY);
    mapper->box(FL_FLAT_BOX);
    mapper->color(FL_WHITE);
    mapper->image(icons["DO_map"]);
    mapper->clear_visible_focus();
    mapper->callback(manage_logout_click, this);

    shop = new Fl_Button((MENUX + (MENUSPACE * 4)), MENUY, MENUSIZEX, MENUSIZEY);
    shop->box(FL_FLAT_BOX);
    shop->color(FL_WHITE);
    shop->image(icons["DO_shop"]);
    shop->clear_visible_focus();
    shop->callback(manage_logout_click, this);

    money = new Fl_Button((MENUX + (MENUSPACE * 5)), MENUY, MENUSIZEX, MENUSIZEY);
    money->box(FL_FLAT_BOX);
    money->color(FL_WHITE);
    money->image(icons["DO_money"]);
    money->clear_visible_focus();
    money->callback(manage_money_click, this);
}

//MANAGER DE SALIR DEL JUEGO
void View::manage_logout_click(Fl_Widget* w, void* user_data){
    View* oribt = static_cast<View*>(user_data);
    oribt->escape = true;
}

//DETERMINA SI EL JUGADOR SE HA RENDIDO
bool View::abort(){
    return escape;
}

//CLICK PARA VER DINERO
void View::manage_money_click(Fl_Widget* w, void* user_data){
    View* oribt = static_cast<View*>(user_data);
    oribt->info->position(INFOX, INFOY);

    //COPYLABEL PARA EL DINERO

    oribt->info->show();
    oribt->frame->redraw();
}



void View::load_planets(){
    for(int i = 0; i < PLANETNUMBER; ++i){
        Fl_Button* star = new Fl_Button(PLANETX + (PLANETSPACING * i), PLANETY, PLANETSIZEX, PLANETSIZEY);
        star->box(FL_NO_BOX);
        star->image(icons["planet"]);
        planets.push_back(star);
    }
}


void View::manage_planet_location(){
    
    // for(){

    // }


    //vector de coordenadas de planetas (0[POSX], 0[POSY])


}






void View::show(){
    frame->show();
}

void View::hide(){
    frame->hide();
}

View::~View(){
    delete frame;
}