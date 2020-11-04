#include <iostream>
#include <ppl.h>
#include <cmath>
#include <vector>
#include <deque>
#include <list>
#include "Function.h"

#define N1 1000
#define N2 50

class My_Class {//Функтор
private:
    double a, b;
public:
    My_Class(double a_ = 0, double b_ = 0) {
        a = a_;
        b = b_;
    }

    double operator()(double x, double y) const {
        double Tmp = 0;
        for (int k = 1; k <= N2; k++)
            for (int j = 1; j <= N2; j++)
                Tmp += cos(k * x) * sin(j * y) / ((k * k + j * j) * sqrt(a * a + b * b + k + j));
        return Tmp;
    }
};

int main() {
//    double clocks;
//
//    std::vector<double> vector(0);
//    std::deque<double> deque(0);
//    std::list<double> list(0);
//    std::vector<double> vectorPar(0);
//    std::deque<double> dequePar(0);
//    std::list<double> listPar(0);
//    for (int i = 1; i < N1; i++) {
//        vector.push_back(100 * cos(i));
//        deque.push_back(100 * cos(i));
//        list.push_back(100 * cos(i));
//        vectorPar.push_back(100 * cos(i));
//        dequePar.push_back(100 * cos(i));
//        listPar.push_back(100 * cos(i));
//    }
//
//    clocks = clock();
//    std::transform(vector.begin(), vector.end(), vector.begin(), calcRow);
//    std::cout << "Time of sequential algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
//
//    clocks = clock();
//    std::transform(deque.begin(), deque.end(), deque.begin(), calcRow);
//    std::cout << "Time of sequential algorithm for deque: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
//
//    clocks = clock();
//    std::transform(list.begin(), list.end(), list.begin(), calcRow);
//    std::cout << "Time of sequential algorithm for list: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
//
//    clocks = clock();
//    concurrency::parallel_transform(vectorPar.begin(), vectorPar.end(), vectorPar.begin(), calcRow);
//    std::cout << "Time of parallel algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
//
//    clocks = clock();
//    concurrency::parallel_transform(dequePar.begin(), dequePar.end(), dequePar.begin(), calcRow);
//    std::cout << "Time of parallel algorithm for deque: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
//
//    clocks = clock();
//    concurrency::parallel_transform(listPar.begin(), listPar.end(), listPar.begin(), calcRow);
//    std::cout << "Time of parallel algorithm for list: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
}