#include <iostream>
#include <ppl.h>
#include <cmath>
#include <vector>

const int COUNT = 5000000;

double fun(double x) {
    return x * x / (1 + x * x) * cos(x);
}

int main() {
    double clocks;

    std::vector<double> vector(0);
    std::vector<double> vectorParallel(0);
    std::vector<double> vectorBuffered(0);

    for (int i = 0; i < COUNT; i++) {
        vector.push_back(fun(i));
        vectorParallel.push_back(fun(i));
        vectorBuffered.push_back(fun(i));
    }

    clocks = clock();
    std::sort(vector.begin(), vector.end());
    std::cout << "Time of sequential algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    concurrency::parallel_sort(vectorParallel.begin(), vectorParallel.end());
    std::cout << "Time of parallel algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    concurrency::parallel_buffered_sort(vectorBuffered.begin(), vectorBuffered.end());
    std::cout << "Time of parallel buffered algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
}