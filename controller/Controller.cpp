#include "Controller.h"
#include <FL/Fl.H>     
#include <FL/fl_draw.H> 
#define LIGHT_ASSAULT 1
#define MEDIUM_ASSAULT 2
#define HEAVY_ASSAULT 3
#define SUP_HEAVY_ASSAULT 4

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
    size_t origin = 0;
    size_t destination = 7;
    size_t dist = c->model.mapNeighbor(POS_UNIT_0, origin, destination);
    size_t solo = 0;
    cout<<endl<<"Dijkstra "<<dist<<" "<<endl;

    // Hay que hacer que origin y destination sean los planetas que escoja el ususario
    // este regresa la distancia que hay entre ese planeta origen y su destino
    // crear una linea entre esos dos ojala de un color diferente a la de floyd
    // y colocar esa distancia en esa arista
    // c->view->mapNeighbor(origin,destination, dist);


}

void Controller::onAgatusClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);

    vector<vector<size_t>> originalMat = c->model.getMatAd();
    vector<vector<size_t>> floydMat = c->model.mapAll(POS_UNIT_1);

        cout<< " Prueba de floyd"<< endl;
    cout << "Matriz de adyacencia:\n";
    for (size_t i = 0; i < originalMat[0].size(); ++i) {
        for (size_t j = 0; j < originalMat[0].size(); ++j) {
            if (floydMat[i][j] == INVALID) {
                cout << "INVALID ";
            } else {
                cout << floydMat[i][j] << " ";
            }
        }
        cout << endl;
    }
    //size_t origin = 0;
    //size_t destination = 7;
    //size_t dist = c->model.mapNeighbor(POS_UNIT_0, origin, destination);
    


    // La vista tiene que tomar el valor de las distancias para las aristas de la matrizOriginal
    // solo si el valor en esa posicion no es invalido EN LAS DOS MATRICES
    // es decir tiene que ser valido en ambas, colocar en la etiqueta los planetas ([i][j], i es un planeta, j otro)
    // como mapeado y colocar las distancias en las aristas
    // c->view->mapAll(originalMat, floydMat);


    //cout << "soy agatus: " <<endl;

}

// Attack button using Greedy Search algorithm
void Controller::onConvictClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);

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

// Attack button using local search algorithm
void Controller::onCharoposClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);

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

// Attack button using exhaustive search algorithm
void Controller::onImpulseClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);

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

// Attack button using exhaustive search bounded algorithm
void Controller::onStigerClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);

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

void Controller::onStreunerClick(Fl_Widget* w, void* userdata) {
      Controller* c = static_cast<Controller*>(userdata);
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

void Controller::onArtemisClick(Fl_Widget* w, void* userdata) {
     Controller* c = static_cast<Controller*>(userdata);
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
