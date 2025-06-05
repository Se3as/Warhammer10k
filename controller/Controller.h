#pragma once

#include "View.h"
#include "Model.h"
#include <iostream>

class Controller {
public:

    Controller(Model& model, View* view);
    void connecctCallbacks();
    void run(); 

private:
    View* view;
    Model& model;  

    static void onInterceptorClick(Fl_Widget* w, void* userdata);
    static void onBarracudaClick(Fl_Widget* w, void* userdata);
    static void onSaboteurClick(Fl_Widget* w, void* userdata);
    static void onAnnihilatorClick(Fl_Widget* w, void* userdata);
    static void onBattlerayClick(Fl_Widget* w, void* userdata);
    static void onBossClick(Fl_Widget* w, void* userdata);
    static void onLogoutClick(Fl_Widget* w, void* userdata);
    static void onAttackClick(Fl_Widget* w, void* userdata);
    static void onExploreClick(Fl_Widget* w, void* userdata);
    static void onMapClick(Fl_Widget* w, void* userdata);
    static void onShopClick(Fl_Widget* w, void* userdata);
    static void onMoneyClick(Fl_Widget* w, void* userdata);
    static void onPlanetClick(Fl_Widget* w, void* userdata);

};
