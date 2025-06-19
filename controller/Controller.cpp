#include "Controller.h"
#include <FL/Fl.H>     
#include <FL/fl_draw.H> 
#define PATHFINDER 1
#define STARMAPPER 4
#define LIGHT_ASSAULT 500
#define MEDIUM_ASSAULT 200
#define HEAVY_ASSAULT 300
#define SUP_HEAVY_ASSAULT 400
#define RAPIDSIGHT 1
#define DEEPPROBE 4

Controller::Controller(Model& model, View* view)
  : model(model),view(view), planet_origin(100), planet_destination(100){}

void Controller::run(){
    string test = "test.csv";
    model.loadGalaxy(test);
    view->initialize();
    this->connectCallbacks();
    Fl::add_timeout(1.0, updateIntervals, this);
    view->show();

    boss_life_text = to_string(model.boss.getBossHP());
    view->boss_life->label(boss_life_text.c_str());

    this->model.setPlayerVisitedPlanets();

    #ifdef DEBUG
    model.printGalaxy();
    this->model.probarDFS();
    this->model.setPlayerVisitedPlanets();
    this->model.probarBFS();
    this->model.probarDijkstra();
    this->model.probarFloyd();
    this->model.setPlayerVisitedPlanets();
    #endif
    Fl::run();
}
void Controller:: connectCallbacks(){

    view->Agatus    ->callback(onAgatusClick, this);
    view->Artemis   ->callback(onArtemisClick,  this);
    view->Charopos   ->callback(onCharoposClick,   this);
    view->Convict   ->callback(onConvictClick,this);
    view->Impulse  ->callback(onImpulseClick,  this);
    view->Reflector  ->callback(onReflectorClick,  this);
    view->Stiger  ->callback(onStigerClick,  this);
    view->Streuner  ->callback(onStreunerClick,  this);

    view->boss->callback(onBossClick, this);

    view->logout ->callback(onLogoutClick, this);
    view->money  ->callback(onMoneyClick, this);

    for (auto planetBtn : view->planets) {
        planetBtn->callback(onPlanetClick, this);
    }

    view->gate->callback(onGateClick, this);

}


void Controller::onReflectorClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    if(c->planet_origin != 100 && c->planet_destination != 100){
        const vector<Galaxy>& galaxies = c->model.getGalaxies();
        const Galaxy& galaxy = galaxies[c->model.getActualGalaxy()];   
        const vector<Planet*>& planetarium = galaxy.getPlanets();
        size_t costExplore = PATHFINDER;

        if(c->model.player.deductEterium(costExplore)){
            c->view->mapping = true;
        }

        size_t dist = c->model.mapNeighbor(POS_UNIT_0, c->planet_origin, c->planet_destination);

        #ifdef DEBUG
        cout<<endl<<"Dijkstra "<<dist<<" "<<endl;
        #endif

        c->view->lineDrawer->add_line(planetarium[c->planet_origin]->getPosX(), planetarium[c->planet_origin]->getPosY(),
            planetarium[c->planet_destination]->getPosX(), planetarium[c->planet_destination]->getPosY(), FL_YELLOW); 
        c->view->frame->redraw();
    }

    c->planet_defaults();
}


void Controller::onAgatusClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    
    // Obtener datos del modelo
    const vector<Galaxy>& galaxies = c->model.getGalaxies();
    const Galaxy& galaxy = galaxies[c->model.getActualGalaxy()];   
    const vector<Planet*>& planetarium = galaxy.getPlanets();
    vector<vector<size_t>> originalMat = c->model.getMatAd();
    vector<vector<size_t>> floydMat = c->model.mapAll(POS_UNIT_1);

    // Verificar si el jugador puede pagar el costo
    size_t costFloyd = PATHFINDER * 2; 
    if(!c->model.player.deductEterium(costFloyd)) {
        #ifdef DEBUG
        cout << "No hay suficiente eterium para usar Agatus" << endl;
        #endif
        return;
    }
    #ifdef DEBUG
    cout << "Matriz de Floyd (distancias más cortas):\n";
    #endif
    for (size_t i = 0; i < floydMat.size(); ++i) {
        for (size_t j = 0; j < floydMat[i].size(); ++j) {
            // Solo mostrar conexiones válidas y únicas (i < j para evitar duplicados)
            if(i < j && floydMat[i][j] != INVALID && originalMat[i][j] != INVALID) {
                // Dibujar la línea entre planetas
                c->view->lineDrawer->add_line(
                    planetarium[i]->getPosX(), planetarium[i]->getPosY(),
                    planetarium[j]->getPosX(), planetarium[j]->getPosY(), 
                    FL_GREEN // Color diferente para Floyd
                );
                // Mostrar información en consola
                #ifdef DEBUG
                cout << "Planeta " << i << " -> Planeta " << j 
                     << ": Distancia original = " << originalMat[i][j] 
                     << ", Distancia más corta = " << floydMat[i][j] << endl;
                #endif
            }
        }
    }

    // Actualizar la vista
    c->view->mapping = true;
    c->view->frame->redraw();
    c->planet_defaults();
}


// Attack button using Greedy Search algorithm
void Controller::onConvictClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);

    shipsAttacks(w, userdata, LIGHT_ASSAULT);

    c->planet_defaults();
}

// Attack button using local search algorithm
void Controller::onCharoposClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);

    shipsAttacks(w, userdata, MEDIUM_ASSAULT);

    c->planet_defaults();
}

// Attack button using exhaustive search algorithm
void Controller::onImpulseClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);

    shipsAttacks(w, userdata, HEAVY_ASSAULT);

    c->planet_defaults();
}

// Attack button using exhaustive search bounded algorithm
void Controller::onStigerClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);

    shipsAttacks(w, userdata, SUP_HEAVY_ASSAULT);

    c->planet_defaults();
}

void Controller::shipsAttacks(Fl_Widget* w, void* userdata, size_t costOfAttack) {
    Controller* c = static_cast<Controller*>(userdata);

    size_t selectShip = 0;
    if (c->model.player.allVisited()) {
        switch (costOfAttack) {
            case LIGHT_ASSAULT:
                #ifdef DEBUG
                std::cout << "Light Assault selected." << std::endl;
                #endif
                selectShip = POS_UNIT_2; 
                break;
            case MEDIUM_ASSAULT:
                #ifdef DEBUG
                std::cout << "Medium Assault selected." << std::endl;
                #endif
                selectShip = POS_UNIT_3; 
                break;
            case HEAVY_ASSAULT:
                #ifdef DEBUG
                std::cout << "Heavy Assault selected." << std::endl;
                #endif
                selectShip = POS_UNIT_4; 
                break;
            case SUP_HEAVY_ASSAULT:
                #ifdef DEBUG
                std::cout << "Super Heavy Assault selected." << std::endl;
                #endif
                selectShip = POS_UNIT_5; 
                break;
            default:
                #ifdef DEBUG
                std::cout << "Unknown assault type." << std::endl;
                #endif
                return;
        }

        if (c->model.player.deductEterium(costOfAttack)) {
                size_t bossLife = c->model.attack(selectShip);
                #ifdef DEBUG
                std::cout << "Boss life after attack: " << bossLife << std::endl;
                #endif
                c->view->updateBossLife(bossLife);
        }  
    }
}

void Controller::onStreunerClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);

    if(c->check_defaults()){

        int index = 6;
        vector<size_t> planetsDiscovered = c->model.explore(index, c->planet_origin);
        #ifdef DEBUG
        cout<<endl;
        for (int i = 0 ; i < planetsDiscovered.size(); i++){
            cout<<" "<< planetsDiscovered[i]<<" "<<endl;
        }
        #endif
    }

    c->planet_defaults();
}

void Controller::onArtemisClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);

    if (!c->check_defaults()) {
        vector<size_t> planetsDiscovered = c->model.explore(POS_UNIT_7, c->planet_origin);
        #ifdef DEBUG
        cout<<endl;
        for (int i = 0 ; i < planetsDiscovered.size(); i++){
            cout<<" "<< planetsDiscovered[i]<<" "<<endl;
        }
        cout<<endl;
        #endif
    }
    c->planet_defaults();
}



void Controller::onBossClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
}


void Controller::onLogoutClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    c->view->escape = true;
    c->view->hide();
}

void Controller::onMoneyClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    
    if (c->view->eterium->visible()) {
        c->view->eterium->hide();
    } else {
        c->view->eterium->show();
    }

    c->view->frame->redraw();
}

void Controller::onGateClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    
    bool notFinished = c->model.notFinished();
    if(c->model.boss.getBossHP() <= 0){        
        if (notFinished){
            c->view->nextGalaxy();

            for (auto planetBtn : c->view->planets) {
                planetBtn->callback(onPlanetClick, c);
            }

            c->model.boss.setBossHP();

            c->model.player.setMines();

            c->view->info->hide();

            c->model.setPlayerVisitedPlanets();

            c->view->frame->redraw();


            c->planet_defaults();
        }
        else{
            c->view->hide();
        }
}
    c->planet_defaults();
    

}


void Controller::onPlanetClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);

    const vector<Galaxy>& galaxies = c->model.getGalaxies();
    const Galaxy& galaxy = galaxies[c->model.getActualGalaxy()];   
    const vector<Planet*>& planetarium = galaxy.getPlanets();

    //buscar el planeta que fue clickeado
    for (size_t i = 0; i < c->view->planets.size(); ++i) {
        if (c->view->planets[i] == w) {

            vector<bool> visited = c->model.player.getPVisited();
            if (visited[i]) {
                c->view->info_visited->position(planetarium[i]->getPosX() - 10, planetarium[i]->getPosY() + 55);
                c->view->info_visited->show();
            }
            vector<bool> mapped = c->model.player.getPMapped();
            if (mapped[i]) {
                c->view->info_mapped->position(planetarium[i]->getPosX() - 10, planetarium[i]->getPosY() + 75);
                c->view->info_mapped->show();
            }
            c->view->frame->redraw();

            size_t clickedPlanet = i;
            
            //logica de seleccion mejorada
            if (c->planet_origin == DEFAULT) {
                //primer planeta seleccionado
                c->planet_origin = clickedPlanet;
                #ifdef DEBUG
                cout << "Planeta origen seleccionado: " << c->planet_origin << endl;
                #endif
            } 
            else if (c->planet_destination == DEFAULT) {
                //segundo planeta seleccionado diferente al origen
                if (clickedPlanet != c->planet_origin) {
                    c->planet_destination = clickedPlanet;
                    #ifdef DEBUG
                    cout << "Planeta destino seleccionado: " << c->planet_destination << endl;
                    #endif
                }
                else {
                    #ifdef DEBUG
                    cout << "Se hizo click en el mismo planeta de origen" << endl;
                    #endif
                }
            }
            else {
                //resetear seleccion si ya hay dos planetas seleccionados
                c->planet_origin = clickedPlanet;
                c->planet_destination = DEFAULT;
                #ifdef DEBUG
                cout << "Reset: nuevo origen = " << c->planet_origin 
                     << ", destino = " << c->planet_destination << endl;
                #endif
            }
            break;
        }
    }
}

void Controller::updateIntervals(void* user_data) {
  Controller* c = static_cast<Controller*>(user_data);

    int totalEterium = c->model.increaseEterium(100 * c->model.player.getMines());

    c->eterium_text = to_string(totalEterium);
    c->view->eterium->label(c->eterium_text.c_str());
    c->view->frame->redraw();


    c->boss_life_text = to_string(c->model.boss.getBossHP());     
    c->view->boss_life->label(c->boss_life_text.c_str());


    Fl::repeat_timeout(1.0, updateIntervals, user_data);
}

void Controller::planet_defaults(){
    planet_origin = DEFAULT;
    planet_destination = DEFAULT;
}

bool Controller::check_defaults(){
    if(planet_origin == DEFAULT && planet_destination == DEFAULT){
        return true;
    } else {
        return false;
    }

}