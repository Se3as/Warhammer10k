#include "Math.h"

int generateRandomNumber(int min, int max){
    int num = min + rand() % (max - min + 1);
    return num;
}

std::vector<Range> divideWindow() {
    const int X0 = 300;
    const int X1 = 900;
    const int Y0 = 100;
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
