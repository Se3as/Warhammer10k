#include "Controller.h"
#include <FL/Fl.H>     
#include <FL/fl_draw.H> 

Controller::Controller(Model& model, View* view)
  : model(model),view(view){}

void Controller::run(){
    string test = "test.csv";
    model.loadGalaxy(test);
    model.printGalaxy();
    view->initialize();
    this->connecctCallbacks();
    // El eterium se actualiza solo
    Fl::add_timeout(1.0, OnEterTimeout, this);
    ////
    view->show();
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
    //view->attack ->callback(onAttackClick, this);
    //view->explore->callback(onExploreClick,this);
    //view->mapper ->callback(onMapClick, this);
    //view->shop   ->callback(onShopClick, this);
    view->money  ->callback(onMoneyClick, this);

    for (auto planetBtn : view->planets) {
        planetBtn->callback(onPlanetClick, this);
    }

    view->gate->callback(onGateClick, this);

}

void Controller::onAgatusClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    size_t origin = 0;
    size_t destination = 7;
    size_t dist = c->model.mapNeighbor(POS_UNIT_0, origin, destination);
    // Hay que hacer que origin y destination sean los planetas que escoja el ususario
    // este regresa la distancia que hay entre ese planeta origen y su destino
    // crear una linea entre esos dos ojala de un color diferente a la de floyd
    // y colocar esa distancia en esa arista
    // c->view->mapNeighbor(origin,destination, dist);
}

void Controller::onArtemisClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    vector<vector<size_t>> originalMat = c->model.getMatAd();
    vector<vector<size_t>> floydMat = c->model.mapAll(POS_UNIT_1);
    // La vista tiene que tomar el valor de las distancias para las aristas de la matrizOriginal
    // solo si el valor en esa posicion no es invalido EN LAS DOS MATRICES
    // es decir tiene que ser valido en ambas, colocar en la etiqueta los planetas ([i][j], i es un planeta, j otro)
    // como mapeado y colocar las distancias en las aristas
    // c->view->mapAll(originalMat, floydMat);
}

void Controller::onCharoposClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    size_t bossLife = c->model.attack(POS_UNIT_2);
    // Actualizar la bossLife.
    //c->view->attackOnBoss(bossLife);
    // Preguntar en el modelo si el boss murio y si si que aparezcal el boton
    // del portal
    // bool dead = c->model.isBossDead();
    // if(dead){
    //  c->view->bossDead();
    //}

}
// TODO: 3 more attack bottons 

void Controller::onConvictClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    vector<size_t> planetsDiscovered = c->model.explore(POS_UNIT_3);
    // Esto regresa un vector con los planetas explorados, recorrerlo y
    // colocar en la etiqueta correspondiente como explorado.
    //c->view->explorePlanets(planetsDiscovered);
}

void Controller::onImpulseClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    vector<size_t> planetsDiscovered = c->model.explore(POS_UNIT_4);
    // Esto regresa un vector con los planetas explorados, recorrerlo y
    // colocar en la etiqueta correspondiente como explorado.
    //c->view->explorePlanets(planetsDiscovered);
}

void Controller::onReflectorClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    vector<size_t> planetsDiscovered = c->model.explore(POS_UNIT_4);
    //c->view->explorePlanets(planetsDiscovered);
}

void Controller::onStigerClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    vector<size_t> planetsDiscovered = c->model.explore(POS_UNIT_4);
    //c->view->explorePlanets(planetsDiscovered);
}

void Controller::onStreunerClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    vector<size_t> planetsDiscovered = c->model.explore(POS_UNIT_4);
    //c->view->explorePlanets(planetsDiscovered);
}

void Controller::onBossClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
}

void Controller::onLogoutClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    c->view->escape = true;
    c->view->hide();
}

// void Controller::onAttackClick(Fl_Widget* w, void* userdata) {
//     Controller* c = static_cast<Controller*>(userdata);
//     c->view->attacking = !c->view->attacking;

// }

// void Controller::onExploreClick(Fl_Widget* w, void* userdata) {
//     Controller* c = static_cast<Controller*>(userdata);
//     c->view->exploring = !c->view->exploring;

// }

// void Controller::onMapClick(Fl_Widget* w, void* userdata) {
//     Controller* c = static_cast<Controller*>(userdata);
//     c->view->mapping = !c->view->mapping;
// }

// void Controller::onShopClick(Fl_Widget* w, void* userdata) {
//     Controller* c = static_cast<Controller*>(userdata);
//     c->view->shopping = !c->view->shopping;
// }

void Controller::onMoneyClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    c->view->info->show();
    c->view->frame->redraw();
}

void Controller::onGateClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    c->view->nextGalaxy();
    c->view->frame->redraw();
}


void Controller::onPlanetClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    for (size_t i = 0; i < c->view->planets.size(); ++i) {
        if (c->view->planets[i] == w) {
            break;
        }
    }
}

void Controller::OnEterTimeout(void* user_data) {
  Controller* c = static_cast<Controller*>(user_data);

    int totalEterium = c->model.increaseEterium(100);
    // Llamar al view para que actualice el eterium
    // c->view->addEterium(totalEterium);
    // c->view->frame->redraw();

    Fl::repeat_timeout(1.0, OnEterTimeout, user_data);
}
