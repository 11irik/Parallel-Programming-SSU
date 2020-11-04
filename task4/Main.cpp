#include <iostream>
#include <ppl.h>
#include <cmath>
#include <vector>

const int COUNT = 500000;

size_t fun(double x) {
    return 4.0e+9 * x * x / (1 + x * x) * cos(x);
}

int main() {
    double clocks;

    std::vector<size_t> X0(COUNT);
    for (int k = 0; k < COUNT; k++) {
        X0[k] = fun(k);
    }

    std::vector<size_t> X(X0);

    clocks = clock();
    sort(X.begin(), X.end());
    std::cout << "Time of sequential algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    X = X0;
    clocks = clock();
    concurrency::parallel_sort(X.begin(), X.end());
    std::cout << "Time of sequential algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    X = X0;
    clocks = clock();
    concurrency::parallel_buffered_sort(X.begin(), X.end());
    std::cout << "Time of sequential algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    X = X0;
    clocks = clock();
    concurrency::parallel_radixsort(X.begin(), X.end());
    std::cout << "Time of sequential algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
}