#include <iostream>
#include <ppl.h>
#include <cmath>
#include <vector>
#include <deque>
#include <list>
#include "Function.h"

const int COUNT = 10;

int main() {
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
    std::transform(vector.begin(), vector.end(), vector.begin(), calcRow);
    std::cout << "Time of sequential algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    std::transform(deque.begin(), deque.end(), deque.begin(), calcRow);
    std::cout << "Time of sequential algorithm for deque: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    std::transform(list.begin(), list.end(), list.begin(), calcRow);
    std::cout << "Time of sequential algorithm for list: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    concurrency::parallel_transform(vectorPar.begin(), vectorPar.end(), vectorPar.begin(), calcRow);
    std::cout << "Time of parallel algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    concurrency::parallel_transform(dequePar.begin(), dequePar.end(), dequePar.begin(), calcRow);
    std::cout << "Time of parallel algorithm for deque: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    concurrency::parallel_transform(listPar.begin(), listPar.end(), listPar.begin(), calcRow);
    std::cout << "Time of parallel algorithm for list: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
}