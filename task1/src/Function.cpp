#include <iostream>
#include <cmath>

double calcRow(double x) {
    double y = 0;

    for (int k = 1; k < std::max(20.0, 20 * abs(x)); k++) {
        for (int j = 1; j < std::max(20.0, 20 * abs(x)); j++) {
            y += (x * x * (k + j)) / (x * x + k * k * k + j * j * j) * cos(k * x) * sin(j * x);
        }
    }
    return y;
}

void calcRowWrap(double &i) {
    i = calcRow(i);
}