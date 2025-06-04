#include "Model.h"
#include "View.h"

//#include "Galaxy.h"

#include <iostream>

using namespace std;

int main() {
    Model model;
    View view;


    string test = "test.csv";
    model.loadGalaxy(test);
    model.printGalaxy();


    view.show();

    while(!view.exterminatused() && !view.abort()){
        Fl::wait();
    }
    
    cout<<"Battle in progress..."<<endl;


    if(view.exterminatused() || view.abort()){
        view.hide();
        Fl::check();
    }


}

