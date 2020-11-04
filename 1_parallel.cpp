#include <iostream>
#include <ppl.h>
#include <cmath>
#include <vector>
#include <deque>
#include <list>
#include "Function.h"

const int COUNT = 10;

void first();
void second();

int main() {
    first();
    second();
}

void first() {
    double clocks;
    double y;

    clocks = clock();
    for (int i = 1; i < COUNT; i++) {
        y = calcRow(100 * cos(i));
    }
    std::cout << "Time of sequential algorithm: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    Concurrency::parallel_for(1, COUNT,
                              [&y](int value) {
                                  y = calcRow(100.0 * cos(value));
                              });
    std::cout << "Time of parallel algorithm: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
}

void second() {
    double clocks;

    std::vector<double> vector(0);
    std::deque<double> deque(0);
    std::list<double> list(0);
    std::vector<double> vectorPar(0);
    std::deque<double> dequePar(0);
    std::list<double> listPar(0);
    for (int i = 1; i < COUNT; i++) {
        vector.push_back(100 * cos(i));
        deque.push_back(100 * cos(i));
        list.push_back(100 * cos(i));
        vectorPar.push_back(100 * cos(i));
        dequePar.push_back(100 * cos(i));
        listPar.push_back(100 * cos(i));
    }

    clocks = clock();
    for_each(vector.begin(), vector.end(), calcRowWrap);
    std::cout << "Time of sequential algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    for_each(deque.begin(), deque.end(), calcRowWrap);
    std::cout << "Time of sequential algorithm for deque: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    for_each(list.begin(), list.end(), calcRowWrap);
    std::cout << "Time of sequential algorithm for list: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    concurrency::parallel_for_each(vectorPar.begin(), vectorPar.end(),
                                   [](double &x) {
                                       x = calcRow(x);
                                   });
    std::cout << "Time of parallel algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    concurrency::parallel_for_each(dequePar.begin(), dequePar.end(),
                                   [](double &x) {
                                       x = calcRow(x);
                                   });
    std::cout << "Time of parallel algorithm for deque: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    concurrency::parallel_for_each(listPar.begin(), listPar.end(),
                                   [](double &x) {
                                       x = calcRow(x);
                                   });
    std::cout << "Time of parallel algorithm for list: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
}