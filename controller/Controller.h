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

    static constexpr int POS_UNIT_0 = 0;
    static constexpr int POS_UNIT_1 = 1;
    static constexpr int POS_UNIT_2 = 2;
    static constexpr int POS_UNIT_3 = 3;
    static constexpr int POS_UNIT_4 = 4;
    static constexpr int POS_UNIT_5 = 5;
    static constexpr int POS_UNIT_6 = 6;
    static constexpr int POS_UNIT_7 = 7;

    static void onAgatusClick(Fl_Widget* w, void* userdata);
    static void onArtemisClick(Fl_Widget* w, void* userdata);
    static void onCharoposClick(Fl_Widget* w, void* userdata);
    static void onConvictClick(Fl_Widget* w, void* userdata);
    static void onImpulseClick(Fl_Widget* w, void* userdata);
    static void onReflectorClick(Fl_Widget* w, void* userdata);
    static void onStigerClick(Fl_Widget* w, void* userdata);
    static void onStreunerClick(Fl_Widget* w, void* userdata);

    static void onBossClick(Fl_Widget* w, void* userdata);
    static void onLogoutClick(Fl_Widget* w, void* userdata);
    //static void onAttackClick(Fl_Widget* w, void* userdata);
    //static void onExploreClick(Fl_Widget* w, void* userdata);
    //static void onMapClick(Fl_Widget* w, void* userdata);
    //static void onShopClick(Fl_Widget* w, void* userdata);
    static void onMoneyClick(Fl_Widget* w, void* userdata);
    static void onPlanetClick(Fl_Widget* w, void* userdata);

    static void onGateClick(Fl_Widget* w, void* userdata);

    static void OnEterTimeout(void* user_data);
};
