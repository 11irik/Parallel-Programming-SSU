#include <iostream>
#include <ppl.h>
#include <cmath>
#include <vector>
#include "Function.h"

const int COUNT = 100;

size_t fun(double x) {
    return 100 * cos(x);
}

int main() {
    double clocks;

    std::vector<size_t> vector(COUNT);
    for (int k = 0; k < COUNT; k++) {
        vector[k] = fun(k);
    }

    std::vector<size_t> vec(vector);

    clocks = clock();
    for (int k = 0; k < COUNT; k++) {
        vec[k] = calcRow(k);
    }
    std::cout << "Time of sequential algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    Concurrency::task_group TGr;
    clocks = clock();
    for (int k = 0; k < COUNT; k++) {
        TGr.run([&vec, k](){vec[k]=calcRow(k);});
    }
    TGr.wait();
    std::cout << "Time of sequential algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
}