#include "Log.h"

Log::Log() {
    srand(static_cast<unsigned>(time(0)));
}
Log::~Log() {
    if (csv.is_open()) {
        csv.close();
    }
}

ofstream& Log::getCsv() {
    return csv;
}

void Log::openCsv() {
    if (!csv.is_open()) {
        csv.open("resultado.csv");
        csv << "unidad,iteraciones,daño,tiempo\n";
    }
}

void Log::closeCsv() {
    if (csv.is_open()) {
        csv.close();
    }
}

void Log::register_noAttack(int iterations, string name, double time) {
    time *= 1000000.0;
    csv << name << "," << iterations << ",0," << time << "\n";
    csv.flush(); 
}

void Log::register_attack(int iterations, string name, size_t daño, double time) {
    time *= 1000000.0;
    csv << name << "," << iterations << ","<< daño <<"," << time << "\n";
    csv.flush(); 
}
