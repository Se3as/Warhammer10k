#include "Log.h"

// Constructor
Log::Log() {
    srand(static_cast<unsigned>(time(0)));
}
Log::~Log() {
    if (csv.is_open()) {
        csv.close();
    }
}

// Get CSV Stream
ofstream& Log::getCsv() {
    return csv;
}

// Open CSV File
void Log::openCsv() {
    if (!csv.is_open()) {
        csv.open("resultado.csv");
        csv << "unidad,iteraciones,daño,tiempo\n";
    }
}

// Close CSV File
void Log::closeCsv() {
    if (csv.is_open()) {
        csv.close();
    }
}

// Register Insert Operation
void Log::register_noAttack(int iterations, string name, double time) {
    csv << name << "," << iterations << ",0," << time << "\n";
    csv.flush(); 
}

// Register Insert Operation
void Log::register_attack(int iterations, string name, size_t daño, double time) {
    csv << name << "," << iterations << ","<< daño <<"," << time << "\n";
    csv.flush(); 
}
