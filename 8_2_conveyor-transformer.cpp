// conveyor-transformer.cpp 
// compile with: /EHsc
#include <agents.h>
#include <cmath>
#include <iostream>
#include <locale.h>
#include <time.h>

int const N = 50;
int const NNN = 1000;
int const Chunk = 100;

double Func1(double x) {
    double Tmp = 0;
    double absX = abs(x);

    for (int n = 0; n <= N; n++) {
        for (int k = 0; k <= N; k++) {
            for (int j = 0; j <= N; j++) {
                double a = std::sqrt(absX + n);
                double b = std::sqrt(1 + absX + std::pow(n, 5)) + std::pow((k * k + j * j), 3.2);
                Tmp += a / b;
            }
        }
    }
    return Tmp;
}

double Func2(double x) {
    double Tmp = 0;
    double absX = abs(x);

    for (int n = 0; n <= N; n++) {
        for (int k = 0; k <= N; k++) {
            for (int j = 0; j <= N; j++) {
                double a = std::sqrt(absX);
                double b = std::sqrt(1 + absX) + std::pow(k, 3) + std::pow(n, 2) + std::pow(j, 2);
                Tmp += a / b;
            }
        }
    }
    return Tmp;
}

int main() {
    double clocks;

    std::vector<double> X(NNN);
    std::vector<double> Y(NNN);
    std::vector<double> Z(NNN);
    for (int k = 0; k < X.size(); k++) {
        X[k] = 10 * sin((double) k);
    }
    clocks = clock();
    for (int k = 0; k < X.size(); k++) {
        Y[k] = Func1(X[k]);
        Y[k] = Func2(Y[k]);
    }
    std::cout << "Time of sequential algorithm: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;

    concurrency::transformer<double, double> t1(Func1), t2(Func2);
    t1.link_target(&t2);

    clocks = clock();
    for (int k = 0; k < Chunk; k++)
        send(t1, X[k]);
    for (int k = Chunk; k < X.size(); k++) {
        Z[k - Chunk] = receive(t2);
        send(t1, X[k]);
    }
    for (int k = X.size() - Chunk; k < X.size(); k++) {
        Z[k] = receive(t2);
    }
    std::cout << "Time of parallel algorithm: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
}
