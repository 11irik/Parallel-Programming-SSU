// conveyor.cpp 
// compile with: /EHsc
#include <agents.h>
#include <ppl.h>
#include <cmath>
#include <iostream>

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

class Stage_Agent : public concurrency::agent {
private:
    concurrency::ISource<double> &_source;
    concurrency::ITarget<double> &_target;

    double (*_func)(double);

public:
    Stage_Agent(concurrency::ISource<double> &source, concurrency::ITarget<double> &target, double func(double))
            : _target(target), _source(source) {
        _func = func;
    }

protected:
    void run() {
        while (true) {
            asend(_target, _func(receive(_source)));
        }
    }
};

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

    concurrency::unbounded_buffer<double> buf0;
    concurrency::unbounded_buffer<double> buf1;
    concurrency::unbounded_buffer<double> buf2;

    Stage_Agent Stage_Agent1(buf0, buf1, Func1);
    Stage_Agent Stage_Agent2(buf1, buf2, Func2);
    Stage_Agent1.start();
    Stage_Agent2.start();

    clocks = clock();
    for (int k = 0; k < Chunk; k++) {
        send(buf0, X[k]);
    }
    for (int k = Chunk; k < X.size(); k++) {
        Z[k - Chunk] = receive(buf2);
        send(buf0, X[k]);
    }
    for (int k = X.size() - Chunk; k < X.size(); k++) {
        Z[k] = receive(buf2);
    }
    std::cout << "Time of parallel algorithm: " << (clock() - clocks) / CLOCKS_PER_SEC << std::endl;
}
