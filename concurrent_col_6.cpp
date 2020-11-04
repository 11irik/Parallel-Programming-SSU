#define _USE_MATH_DEFINES

#include <iostream>
#include <ppl.h>
#include <cmath>
#include <vector>
#include <concurrent_vector.h>
#include <concurrent_queue.h>
#include "Function.h"

#define N1 200
#define N2 50

const int COUNT = 100;

struct Point {
    double x;
    double y;
    double f;

    Point(double _x, double _y, double _f) {
        x = _x;
        y = _y;
        f = _f;
    }
};

int main() {
    double clocks;

    std::vector<Point> Pts;
    double h = 2.0 * M_PI / N1;
    clocks = clock();
    for (int k = 0; k < N1; k++) {
        for (int j = 0; j < N1; j++) {
            double x = h * k;
            double y = h * j;
            double f = calcTwiceRow(x, y, N2);
            if (f >= 0) {
                Pts.push_back(Point(x, y, f));
            }
        }
    }
    std::cout << "Time of sequential algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
    Pts.clear();

    concurrency::concurrent_vector<Point> CPts;
    clocks = clock();
    concurrency::parallel_for(0, N1,
                              [&CPts, h](int k) {
                                  for (int j = 0; j < N1; j++) {
                                      double x = h * k;
                                      double y = h * j;
                                      double f = calcTwiceRow(x, y, N2);
                                      if (f >= 0) CPts.push_back(Point(x, y, f));
                                  }
                              }

    );
    std::cout << "Time of sequential algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
    CPts.clear();

    concurrency::concurrent_queue<Point> QPts;
    clocks = clock();
    concurrency::parallel_for(0, N1,
                              [&QPts, h](int k) {
                                  for (int j = 0; j < N1; j++) {
                                      double x = h * k;
                                      double y = h * j;
                                      double f = calcTwiceRow(x, y, N2);
                                      if (f >= 0) QPts.push(Point(x, y, f));
                                  }
                              }
    );
    std::cout << "Time of sequential algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
    QPts.clear();
}