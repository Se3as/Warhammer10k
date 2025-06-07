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
    view->show();
    // std::cout << "LightAssault test, greedy search. About to attack..." << std::endl;
    // size_t bossLife = this->model.attack(POS_UNIT_2);
    // std::cout << "Boss life after attack using greedy search: " << bossLife << std::endl;

    // std::cout << "MediumAssault test, local search. About to attack..." << std::endl;
    // size_t bossLife = this->model.attack(POS_UNIT_3);
    // std::cout << "Boss life after attack local search: " << bossLife << std::endl;

    // std::cout << "HeavyAssault test, exhaustive search. About to attack..." << std::endl;
    // size_t bossLife = this->model.attack(POS_UNIT_4);
    // std::cout << "Boss life after attack exhaustive search: " << bossLife << std::endl;

    // std::cout << "SupHeavyAssault test, exhaustive search bounded. About to attack..." << std::endl;
    size_t bossLife = this->model.attack(POS_UNIT_5);
    std::cout << "Boss life after attack exhaustive search bounded: " << bossLife << std::endl;

    Fl::run();
}
void Controller:: connecctCallbacks(){

    view->interceptor->callback(onInterceptorClick, this);
    view->barracuda  ->callback(onBarracudaClick,  this);
    view->saboteur   ->callback(onSaboteurClick,   this);
    view->annihilator->callback(onAnnihilatorClick,this);
    view->battleray  ->callback(onBattlerayClick,  this);

    view->boss->callback(onBossClick, this);

    view->logout ->callback(onLogoutClick, this);
    view->attack ->callback(onAttackClick, this);
    view->explore->callback(onExploreClick,this);
    view->mapper ->callback(onMapClick, this);
    view->shop   ->callback(onShopClick, this);
    view->money  ->callback(onMoneyClick, this);

    for (auto planetBtn : view->planets) {
        planetBtn->callback(onPlanetClick, this);
    }
}

void Controller::onInterceptorClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    // c->model.map_neighbor(POS_UNIT_0);
}

void Controller::onBarracudaClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    // c->model.map_all(POS_UNIT_1);
}

void Controller::onSaboteurClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    size_t bossLife = c->model.attack(POS_UNIT_2);
    //c->view->attackOnBoss(bossLife);
}
// TODO: 3 more attack bottons 

void Controller::onAnnihilatorClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    vector<size_t> planetsDiscovered = c->model.explore(POS_UNIT_3);
    //c->view->explorePlanets(planetsDiscovered);
}

void Controller::onBattlerayClick(Fl_Widget* w, void* userdata) {
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

void Controller::onAttackClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    c->view->attacking = !c->view->attacking;

}

void Controller::onExploreClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    c->view->exploring = !c->view->exploring;

}

void Controller::onMapClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    c->view->mapping = !c->view->mapping;
}

void Controller::onShopClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    c->view->shopping = !c->view->shopping;
}

void Controller::onMoneyClick(Fl_Widget* w, void* userdata) {
    Controller* c = static_cast<Controller*>(userdata);
    c->view->info->show();
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
