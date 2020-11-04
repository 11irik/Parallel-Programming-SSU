#include <iostream>
#include <ppl.h>
#include <vector>
#include "Function.h"

const int COUNT = 10;

int main() {
    double clocks;
    double array[COUNT];

    clocks = clock();
    for (int i = 0; i < COUNT; i++) {
        array[i] = calcRow(100 * cos(i));
    }
    std::cout << "Sequential algorithm: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
//    TODO: read about lambda and parallel_for
    Concurrency::parallel_for(0, COUNT,
                              [&array](size_t i) {
                                  array[i] = calcRow(100 * cos(i));
                              });
    std::cout << "Parallel algorithm: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
}
