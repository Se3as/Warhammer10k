#include "Math.h"

int generateRandomNumber(int min, int max){
    int num = min + rand() % (max - min + 1);
    return num;
}

pair<int, int> generateUniqueCoordinate(set<pair<int, int>>& takenCoordinates,
    int max_X, int max_Y){
    int x,y;
    pair<int, int> coord;
    while (true) {
        x = generateRandomNumber(0, max_X);
        y = generateRandomNumber(0, max_Y);
        coord = make_pair(x, y);
        if (takenCoordinates.count(coord) == 0) {
            break;
        }
    }
    takenCoordinates.insert(coord);
    return coord;
}
