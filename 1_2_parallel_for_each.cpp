#include <iostream>
#include <ppl.h>
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
    for (int i = 1; i < COUNT; i++) {
        vector.push_back(100 * cos(i));
        deque.push_back(100 * cos(i));
        list.push_back(100 * cos(i));
    }
    std::vector<double> vectorPar(vector);
    std::deque<double> dequePar(deque);
    std::list<double> listPar(list);

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
    concurrency::parallel_for_each(vectorPar.begin(), vectorPar.end(),calcRowWrap);
    std::cout << "Time of parallel algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    concurrency::parallel_for_each(dequePar.begin(), dequePar.end(),calcRowWrap);
    std::cout << "Time of parallel algorithm for deque: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    concurrency::parallel_for_each(listPar.begin(), listPar.end(), calcRowWrap);
    std::cout << "Time of parallel algorithm for list: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
}
