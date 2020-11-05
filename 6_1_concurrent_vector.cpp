#define _USE_MATH_DEFINES
#include <iostream>
#include <ppl.h>
#include <cmath>
#include <vector>
#include <concurrent_vector.h>
#include "Function.h"

#define N1 200
#define N2 50

int main() {
    double clocks;

    std::vector<Point> points;
    double h = 2.0 * M_PI / N1;
    clocks = clock();
    for (int k = 0; k < N1; k++) {
        for (int j = 0; j < N1; j++) {
            double x = h * k;
            double y = h * j;
            double f = calcTwiceRow(x, y, N2);
            //            TODO: condition?
            if (f >= 0) {
                points.push_back(Point(x, y, f));
            }
        }
    }
    std::cout << "Time of sequential algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    concurrency::concurrent_vector<Point> concurrentPoints;
    clocks = clock();
    concurrency::parallel_for(0, N1,
                              [&concurrentPoints, h](int k) {
                                  for (int j = 0; j < N1; j++) {
                                      double x = h * k;
                                      double y = h * j;
                                      double f = calcTwiceRow(x, y, N2);
                                      if (f >= 0) concurrentPoints.push_back(Point(x, y, f));
                                  }
                              }

    );
    std::cout << "Time of parallel algorithm for concurrent vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
}