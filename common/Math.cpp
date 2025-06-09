#include "Math.h"
#include <cmath>

int generateRandomNumber(int min, int max){
    int num = min + rand() % (max - min + 1);
    return num;
}

std::vector<Range> divideWindow() {
    const int X0 = 200;
    const int X1 = 1000;
    const int Y0 = 50;
    const int Y1 = 520;
    const int N  = 20;
    const int wide = (X1 - X0) / N;  

    std::vector<Range> parts;
    parts.reserve(N);

    for (int i = 0; i < N; ++i) {
        int xi = X0 + i * wide;
        int xf = xi + wide;
        if (i == N - 1) {
            xf = X1;  
        }

        parts.push_back({ xi, xf, Y0, Y1 });
    }

    return parts;
}


pair<int, int> generateUniqueCoordinate(
    const pair<int, int>& xRange,
    const pair<int, int>& yRange)
{
    int x, y;
    pair<int, int> coord;
    x = generateRandomNumber(xRange.first,  xRange.second);
    y = generateRandomNumber(yRange.first,  yRange.second);
    coord = make_pair(x, y);

    return coord;
}

size_t distanceTwoPoints(size_t x1, size_t y1, size_t x2, size_t y2) {
    double dx = double(x2) - double(x1);
    double dy = double(y2) - double(y1);
    return static_cast<size_t>(sqrt(dx*dx + dy*dy));
}
