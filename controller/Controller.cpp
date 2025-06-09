#include "Controller.h"
#include <FL/Fl.H>     
#include <FL/fl_draw.H> 
#define PATHFINDER 1
#define STARMAPPER 4
#define LIGHT_ASSAULT 1
#define MEDIUM_ASSAULT 2
#define HEAVY_ASSAULT 3
#define SUP_HEAVY_ASSAULT 4
#define RAPIDSIGHT 1
#define DEEPPROBE 4

Controller::Controller(Model& model, View* view)
  : model(model),view(view), planet_origin(100), planet_destination(100){}

void Controller::run(){
    string test = "test.csv";
    model.loadGalaxy(test);
    model.printGalaxy();
    view->initialize();
    this->connecctCallbacks();
    // El eterium se actualiza solo
    Fl::add_timeout(1.0, updateIntervals, this);
    ////
    view->show();

    boss_life_text = to_string(model.boss.getBossHP());
    view->boss_life->label(boss_life_text.c_str());

    // Estos son pruebas para los algoritmos
    this->model.setPlayerVisitedPlanets();
    // Imprime los vecinos de cada nodo que son lo que devuelve cuando se manda la nava
    this->model.probarBFS();
    // En este momento no imprime nada porque todos los nodos fueron visitados por BFS
    this->model.probarDFS();
    // Imprime la minima distancia que hay entre nodo 0 y 7, debe ser igual al valor de esa posicion del floyd
    this->model.probarDijkstra();
    // Imprime la matriz con las minimas distancias
    this->model.probarFloyd();

    /////////////
    Fl::run();
}
void Controller:: connecctCallbacks(){

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

    const vector<Galaxy>& galaxies = c->model.getGalaxies();
    const Galaxy& galaxy = galaxies[c->model.getActualGalaxy()];   
    const vector<Planet*>& planetarium = galaxy.getPlanets();

    if(!c->check_defaults()){

        size_t costExplore = PATHFINDER;
        if(c->model.player.deductEterium(costExplore)){
            c->view->mapping = true;
        }

        

        size_t dist = c->model.mapNeighbor(POS_UNIT_0, c->planet_origin, c->planet_destination);

        cout<<endl<<"Dijkstra "<<dist<<" "<<endl;

        //MOSTRAR LA CONEXION
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
    size_t costFloyd = PATHFINDER * 2; // Costo mayor para Floyd
    if(!c->model.player.deductEterium(costFloyd)) {
        cout << "No hay suficiente eterium para usar Agatus" << endl;
        return;
    }

    cout << "Matriz de Floyd (distancias más cortas):\n";
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
                cout << "Planeta " << i << " -> Planeta " << j 
                     << ": Distancia original = " << originalMat[i][j] 
                     << ", Distancia más corta = " << floydMat[i][j] << endl;
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

    if(!c->check_defaults()){

        size_t costOfAttack = LIGHT_ASSAULT; // cost defined at the top of this file

        // TODO(any) check this c->model.player.getEterium();
        // cout << "Eterium before attack: " << currentEterium << endl;

        // if the player has enough eterium, attack the boss
        // if (c->model.player.getEterium() >= costOfAttack) {
            c->model.player.deductEterium(costOfAttack); // Deduct eterium cost
            // c->view->updateEterium(c->model.player.getEterium());
            std::cout << "LightAssault start. About to attack..." << std::endl;
            size_t bossLife = c->model.attack(POS_UNIT_2);
            std::cout << "Boss life after attack: " << bossLife << std::endl;
            // c->view->updateBossLife(bossLife);

            // Check if the boss is dead and update the view accordingly
            // Also show the portal button if the boss is dead
            if (c->model.boss.getBossHP() == 0) {
                // c->view->bossDead();  // TODO(any) Define this method
                // c->view->showPortalButton(); // TODO(any) Define this method
            }
        // } else {
            // Show a message indicating insufficient eterium or other thing
            // c->view->showInsufficientEteriumMessage(); // TODO(any) Define this method
        // }

        // Instructions to follow
        // size_t bossLife = c->model.attack(POS_UNIT_2);
        // Actualizar la bossLife.
        //c->view->attackOnBoss(bossLife);
        // Preguntar en el modelo si el boss murio y si si que aparezcal el boton
        // del portal
        // bool dead = c->model.isBossDead();
        // if(dead){
        //  c->view->bossDead();
        //}
    }

    c->planet_defaults();
}

// Attack button using local search algorithm
void Controller::onCharoposClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);

    if(!c->check_defaults()){

        size_t costOfAttack = MEDIUM_ASSAULT; // cost defined at the top of this file

        // if the player has enough eterium, attack the boss
        // if (c->model.player.getEterium() >= costOfAttack) {
            c->model.player.deductEterium(costOfAttack); // Deduct eterium cost
            // c->view->updateEterium(c->model.player.getEterium());
            std::cout << "MediumAssault start. About to attack..." << std::endl;
            size_t bossLife = c->model.attack(POS_UNIT_3);
            std::cout << "Boss life after attack: " << bossLife << std::endl;
            // c->view->updateBossLife(bossLife);

            // Check if the boss is dead and update the view accordingly
            // Also show the portal button if the boss is dead
            if (c->model.boss.getBossHP() == 0) {
                //c->view->bossDead();  // TODO(any) Define this method
                //c->view->showPortalButton(); // TODO(any) Define this method
            }
        // } else {
            // Show a message indicating insufficient eterium or other thing
            //c->view->showInsufficientEteriumMessage(); // TODO(any) Define this method
        //}
    }

    c->planet_defaults();
}

// Attack button using exhaustive search algorithm
void Controller::onImpulseClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);

    if(!c->check_defaults()){

        size_t costOfAttack = HEAVY_ASSAULT; // cost defined at the top of this file

        // if the player has enough eterium, attack the boss
        // if (c->model.player.getEterium() >= costOfAttack) {
            c->model.player.deductEterium(costOfAttack); // Deduct eterium cost
            // c->view->updateEterium(c->model.player.getEterium());
            std::cout << "HeavyAssault start. About to attack..." << std::endl;
            size_t bossLife = c->model.attack(POS_UNIT_4);
            std::cout << "Boss life after attack: " << bossLife << std::endl;
            // c->view->updateBossLife(bossLife);

            // Check if the boss is dead and update the view accordingly
            // Also show the portal button if the boss is dead
            if (c->model.boss.getBossHP() == 0) {
                //c->view->bossDead();  // TODO(any) Define this method
                //c->view->showPortalButton(); // TODO(any) Define this method
            }
        // } else {
            // Show a message indicating insufficient eterium or other thing
            //c->view->showInsufficientEteriumMessage(); // TODO(any) Define this method
        //}
    }

    c->planet_defaults();
}

// Attack button using exhaustive search bounded algorithm
void Controller::onStigerClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);

    if(!c->check_defaults()){
    
        size_t costOfAttack = SUP_HEAVY_ASSAULT; // cost defined at the top of this file

        // if the player has enough eterium, attack the boss
        // if (c->model.player.getEterium() >= costOfAttack) {
            c->model.player.deductEterium(costOfAttack); // Deduct eterium cost
            // c->view->updateEterium(c->model.player.getEterium());
            std::cout << "SuperHeavyAssault start. About to attack..." << std::endl;
            size_t bossLife = c->model.attack(POS_UNIT_5);
            std::cout << "Boss life after attack: " << bossLife << std::endl;
            // c->view->updateBossLife(bossLife);

            // Check if the boss is dead and update the view accordingly
            // Also show the portal button if the boss is dead
            if (c->model.boss.getBossHP() == 0) {
                //c->view->bossDead();  // TODO(any) Define this method
                //c->view->showPortalButton(); // TODO(any) Define this method
            }
        // } else {
            // Show a message indicating insufficient eterium or other thing
            //c->view->showInsufficientEteriumMessage(); // TODO(any) Define this method
        //}
    }

    c->planet_defaults();
}

void Controller::onStreunerClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);

    if(!c->check_defaults()){

        int index = 6;
        vector<size_t> planetsDiscovered = c->model.explore(index);
        cout<<endl;
        for (int i = 0 ; i < planetsDiscovered.size(); i++){
            cout<<" "<< planetsDiscovered[i]<<" "<<endl;
        }
        //c->view->explorePlanets(planetsDiscovered);

        // Esto regresa un vector con los planetas explorados, recorrerlo y
        // colocar en la etiqueta correspondiente como explorado.
        //c->view->explorePlanets(planetsDiscovered);
    }

    c->planet_defaults();
}

void Controller::onArtemisClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);

    if(!c->check_defaults()){

        vector<size_t> planetsDiscovered = c->model.explore(POS_UNIT_7);
            cout<<endl;
        for (int i = 0 ; i < planetsDiscovered.size(); i++){
            cout<<" "<< planetsDiscovered[i]<<" "<<endl;
        }
        cout<<endl;
        //c->view->explorePlanets(planetsDiscovered);

        // Esto regresa un vector con los planetas explorados, recorrerlo y
        // colocar en la etiqueta correspondiente como explorado.
        //c->view->explorePlanets(planetsDiscovered);
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
    
    if(c->model.boss.getBossHP() <= 0){         //<---- COMPROBAR QUE SE ACTUALIZA LA VIDA DEL BOSS!!!!

        c->view->nextGalaxy();

        for (auto planetBtn : c->view->planets) {
            planetBtn->callback(onPlanetClick, c);
        }

        c->model.boss.setBossHP();

        // c->boss_life_text = to_string(c->model.boss.getBossHP());
        // c->view->boss_life->label(c->boss_life_text.c_str());

        c->model.setPlayerVisitedPlanets();

        c->view->frame->redraw();

        c->planet_defaults();
    }
    
    c->planet_defaults();
}


void Controller::onPlanetClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    
    //buscar el planeta que fue clickeado
    for (size_t i = 0; i < c->view->planets.size(); ++i) {
        if (c->view->planets[i] == w) {
            size_t clickedPlanet = i;
            
            //logica de seleccion mejorada
            if (c->planet_origin == DEFAULT) {
                //primer planeta seleccionado
                c->planet_origin = clickedPlanet;
                cout << "Planeta origen seleccionado: " << c->planet_origin << endl;
            } 
            else if (c->planet_destination == DEFAULT) {
                //segundo planeta seleccionado diferente al origen
                if (clickedPlanet != c->planet_origin) {
                    c->planet_destination = clickedPlanet;
                    cout << "Planeta destino seleccionado: " << c->planet_destination << endl;
                    
                }
                else {
                    cout << "Se hizo click en el mismo planeta de origen" << endl;
                }
            }
            else {
                //resetear seleccion si ya hay dos planetas seleccionados
                c->planet_origin = clickedPlanet;
                c->planet_destination = DEFAULT;
                cout << "Reset: nuevo origen = " << c->planet_origin 
                     << ", destino = " << c->planet_destination << endl;
            }
            break;
        }
    }
}

void Controller::updateIntervals(void* user_data) {
  Controller* c = static_cast<Controller*>(user_data);

    int totalEterium = c->model.increaseEterium(100);
    
    // Llamar al view para que actualice el eterium
    c->eterium_text = to_string(totalEterium);
    c->view->eterium->label(c->eterium_text.c_str());
    c->view->frame->redraw();


    c->boss_life_text = to_string(c->model.boss.getBossHP());      //<--- COMPROBAR QUE SE BAJA LA VIDA DEL BOSS
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