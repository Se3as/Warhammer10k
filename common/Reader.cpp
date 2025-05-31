#include "Reader.h"

vector<vector<string>> readCSV(const string& filename) {
    vector<vector<string>> rows;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file : " << filename << "\n";
        return rows;
    }

    string line;
    if (!getline(file, line)) {
        cerr << "Error: Could not read headers in : " << filename << "\n";
        return rows;
    }

    while (getline(file, line)) {
        vector<string> cols;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) {
            cols.push_back(cell);
        }
        rows.push_back(move(cols));
    }

    file.close();
    return rows;
}
