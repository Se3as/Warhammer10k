#include "View.h"
#include "Controller.h"
#include "Model.h"

int main(int argc, char** argv) {

    Model model;
    View* view = new View(model);      
    Controller* controller = new Controller(model, view);

    controller->run();

    delete controller;
    delete view;
    return 0;
}
