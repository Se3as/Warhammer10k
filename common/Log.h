#pragma once

#include <fstream>
#include <string>
#include <ctime>
#include <iostream>

using namespace std;
class Log {
    private:
        ofstream csv;
    public:
        Log();
        ~Log();
        ofstream& getCsv();

        void openCsv();


        void register_noAttack(int iterations, string name, double time);
        void register_attack(int iterations, string name, size_t daño, double time);

        void closeCsv();
};