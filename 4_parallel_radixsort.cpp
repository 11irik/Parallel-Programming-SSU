#include <iostream>
#include <ppl.h>
#include <cmath>
#include <vector>

const int COUNT = 5000000;

size_t fun(size_t x) {
    return 4.0e+9 * x * x / (1 + x * x) * cos(x);
}

int main() {
    double clocks;

    std::vector<size_t> vector(0);
    for (int i = 0; i < COUNT; i++) {
        vector.push_back(fun(i));
    }
    std::vector<size_t> vectorParallel(vector);
    std::vector<size_t> vectorBuffered(vector);
    std::vector<size_t> vectorRadix(vector);

    clocks = clock();
    sort(vector.begin(), vector.end());
    std::cout << "Time of sequential algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    concurrency::parallel_sort(vectorParallel.begin(), vectorParallel.end());
    std::cout << "Time of parallel algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    concurrency::parallel_buffered_sort(vectorBuffered.begin(), vectorBuffered.end());
    std::cout << "Time of parallel buffered algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    clocks = clock();
    concurrency::parallel_radixsort(vectorRadix.begin(), vectorRadix.end());
    std::cout << "Time of parallel radixsort algorithm for vector: " << (clock() - clocks) / CLOCKS_PER_SEC
              << std::endl;
}