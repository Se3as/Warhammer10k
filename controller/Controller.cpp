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

    std::cout << "LightAssault test, greedy search. About to attack..." << std::endl;
    size_t bossLife1 = this->model.greedyAttack(POS_UNIT_2);
    std::cout << "Boss life after attack using greedy search: " << bossLife1 << std::endl;

    std::cout << "MediumAssault test, local search. About to attack..." << std::endl;
    size_t bossLife2 = this->model.localAttack(POS_UNIT_3);
    std::cout << "Boss life after attack local search: " << bossLife2 << std::endl;

    std::cout << "HeavyAssault test, exhaustive search. About to attack..." << std::endl;
    size_t bossLife3 = this->model.exhaustiveAttack(POS_UNIT_4);
    std::cout << "Boss life after attack exhaustive search: " << bossLife3 << std::endl;

    std::cout << "SupHeavyAssault test, exhaustive search bounded. About to attack..." << std::endl;
    size_t bossLife4 = this->model.exhaustiveBoundedAttack(POS_UNIT_5);
    std::cout << "Boss life after attack exhaustive search bounded: " << bossLife4 << std::endl;

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
    vector<size_t> planetsDiscovered = c->model.explore(POS_UNIT_4);
    //c->view->explorePlanets(planetsDiscovered);
}

void Controller::onAgatusClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    size_t origin = 0;
    size_t destination = 7;
    //size_t dist = c->model.mapNeighbor(POS_UNIT_0, origin, destination);
    // Hay que hacer que origin y destination sean los planetas que escoja el ususario
    // este regresa la distancia que hay entre ese planeta origen y su destino
    // crear una linea entre esos dos ojala de un color diferente a la de floyd
    // y colocar esa distancia en esa arista
    // c->view->mapNeighbor(origin,destination, dist);


    cout << "soy agatus: " <<endl;

}

void Controller::onConvictClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    vector<size_t> planetsDiscovered = c->model.explore(POS_UNIT_3);
    // Esto regresa un vector con los planetas explorados, recorrerlo y
    // colocar en la etiqueta correspondiente como explorado.
    //c->view->explorePlanets(planetsDiscovered);
}

void Controller::onCharoposClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
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

void Controller::onImpulseClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    vector<size_t> planetsDiscovered = c->model.explore(POS_UNIT_4);
    // Esto regresa un vector con los planetas explorados, recorrerlo y
    // colocar en la etiqueta correspondiente como explorado.
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
    c->view->info->show();
    c->view->frame->redraw();
}

void Controller::onGateClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    c->view->nextGalaxy();

    for (auto planetBtn : c->view->planets) {
        planetBtn->callback(onPlanetClick, c);
    }

    c->model.boss.setBossHP();

    c->boss_life_text = to_string(c->model.boss.getBossHP());
    c->view->boss_life->label(c->boss_life_text.c_str());


    c->view->frame->redraw();

}


void Controller::onPlanetClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    for (size_t i = 0; i < c->view->planets.size(); ++i) {
        if (c->view->planets[i] == w) {
            cout<<"soy el planeta: " << i <<endl;
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
