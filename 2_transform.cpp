#include <iostream>
#include <ppl.h>
#include <cmath>
#include <vector>
#include <deque>
#include <list>
#include "Function.h"

const int COUNT = 20;

int main() {
    double clocks;

    std::vector<double> vectorX(0);
    std::deque<double> dequeX(0);
    std::list<double> listX(0);
    for (int i = 0; i < COUNT; i++) {
        vectorX.push_back(100 * cos(i));
        dequeX.push_back(100 * cos(i));
        listX.push_back(100 * cos(i));
    }
    std::vector<double> vectorY(COUNT);
    std::deque<double> dequeY(COUNT);
    std::list<double> listY(COUNT);

    clocks = clock();
    std::transform(vectorX.begin(), vectorX.end(), vectorY.begin(), calcRow);
    std::cout << "Time of sequential algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    std::transform(dequeX.begin(), dequeX.end(), dequeY.begin(), calcRow);
    std::cout << "Time of sequential algorithm for deque: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    std::transform(listX.begin(), listX.end(), listY.begin(), calcRow);
    std::cout << "Time of sequential algorithm for list: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    concurrency::parallel_transform(vectorX.begin(), vectorX.end(), vectorY.begin(), calcRow);
    std::cout << "Time of parallel algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    concurrency::parallel_transform(dequeX.begin(), dequeX.end(), dequeX.begin(), calcRow);
    std::cout << "Time of parallel algorithm for deque: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    concurrency::parallel_transform(listX.begin(), listX.end(), listY.begin(), calcRow);
    std::cout << "Time of parallel algorithm for list: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
}