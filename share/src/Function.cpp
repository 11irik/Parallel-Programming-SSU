#include <iostream>
#include <cmath>
#include "Function.h"

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

double calcTwiceRow(double x, double y, int n) {
    double tmp = 0;

    for (int k = 1; k <= n; k++) {
        for (int j = 1; j <= n; j++) {
            tmp += cos(k * x) * sin(j * y) / ((1 + k + j) * sqrt(1 + pow(k, 4) + pow(j, 4)));
        }
    }
    return tmp;
}

