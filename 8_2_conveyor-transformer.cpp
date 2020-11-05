// conveyor-transformer.cpp 
// compile with: /EHsc
#include <agents.h>
#include <cmath>
#include <iostream>
#include <locale.h>
#include <time.h>

int const N = 100;
int const NNN = 1000;
int const Chunk = 100;

//TODO: NOT READY
double Func1(double x) {
    double Tmp = 0;
    double Tmpa = abs(x);

    for (int n = 0; n <= N; n++) {
        double Tmpxn = x + n;
        double Tmpn3 = n * n * n;
        for (int k = 0; k <= N; k++) {
            double Tmpk = k * k;
            for (int j = 0; j <= N; j++) {
                Tmp += Tmpxn / (1 + Tmpa + Tmpn3 + k * k + j * j);
            }
        }
    }
    return Tmp;
}

double Func2(double x) {
    double Tmp = 0;
    double Tmpa = abs(x);
    for (int n = 0; n <= N; n++) {
        double Tmpn = n * n;
        for (int k = 0; k <= N; k++) {
            double Tmpk = k * k * k;
            for (int j = 0; j <= N; j++) {
                Tmp += 1.0 / (1 + Tmpa + Tmpn + Tmpk + j * j);
            }
        }
    }
    return x * Tmp;
}

//TODO: FIXME
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

    // t1 -> t2 -> t3 -> t4
    concurrency::transformer<double, double> t1(Func1), t2(Func2);
    t1.link_target(&t2);

    clocks = clock();
    for (int k = 0; k < Chunk; k++) {
        send(t1, X[k]);
    }
    std::cout << "Time of parallel algorithm: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
}
