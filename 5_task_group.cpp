#include <iostream>
#include <ppl.h>
#include <cmath>
#include <vector>
#include "Function.h"

const int COUNT = 100;

double fun(double x) {
    return 100 * cos(x);
}

int main() {
    double clocks;

    double array[COUNT];

    clocks = clock();
    for (int k = 0; k < COUNT; k++) {
        array[k] = calcRow(k);
    }
    std::cout << "Time of sequential algorithm: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    Concurrency::task_group TGr;
    clocks = clock();
    for (int k = 0; k < COUNT; k++) {
        TGr.run([&array, k](){array[k]=calcRow(k);});
    }
    TGr.wait();
    std::cout << "Time of parallel algorithm: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
}