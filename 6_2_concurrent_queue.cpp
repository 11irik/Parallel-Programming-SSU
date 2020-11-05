#define _USE_MATH_DEFINES
#include <iostream>
#include <ppl.h>
#include <cmath>
#include <queue>
#include <concurrent_queue.h>
#include "Function.h"

#define N1 200
#define N2 50

const int COUNT = 100;

int main() {
    double clocks;

    std::queue<Point> points;
    double h = 2.0 * M_PI / N1;
    clocks = clock();
    for (int k = 0; k < N1; k++) {
        for (int j = 0; j < N1; j++) {
            double x = h * k;
            double y = h * j;
            double f = calcTwiceRow(x, y, N2);
//            TODO: condition?
            if (f >= 0) {
                points.push(Point(x, y, f));
            }
        }
    }
    std::cout << "Time of sequential algorithm for queue: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    concurrency::concurrent_queue<Point> concurrentPoints;
    clocks = clock();
    concurrency::parallel_for(0, N1,
                              [&concurrentPoints, h](int k) {
                                  for (int j = 0; j < N1; j++) {
                                      double x = h * k;
                                      double y = h * j;
                                      double f = calcTwiceRow(x, y, N2);
                                      if (f >= 0) concurrentPoints.push(Point(x, y, f));
                                  }
                              }
    );
    std::cout << "Time of parallel algorithm for concurrent queue: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
}