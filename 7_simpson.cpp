#define _USE_MATH_DEFINES

#include <iostream>
#include <ppl.h>
#include <cmath>
#include "Concurrent_Simps.h"

class My_Class {
private:
    double y;
    const int NNN = 200000;
    const double _Inf = 5000.0;

public:
    My_Class(double _y = 0.0) {
        y = _y;
    }

    double Sub_Int_Func(double x) {
        double Tmp = 15 * log(10.0) + log(abs(x)) - sqrt(x);
        int N = Tmp > 0 ? ceil(Tmp * Tmp + 1) : 1;
        double P = exp(-sqrt(abs(x)));
        double Tmp2 = sqrt(y * y + x * x);
        for (int k = 0; k <= N; k++) {
            P *= cos(x / (Tmp2 + exp(sqrt((double) k))));
        }
        return P;
    }

    double Quad() {
        return MethodCall::Simpson(0.0, _Inf, NNN,
                                   [this](double x) { return Sub_Int_Func(x); });
    }

    double Concurrent_Quad() {
        return MethodCall::Concurrent_Simpson(0.0, _Inf, NNN,
                                              [this](double x) { return Sub_Int_Func(x); });
    }
};

int main() {
    double clocks;
    double F;
    double y;
    std::cout << "Enter y: ";
    std::cin >> y;
    My_Class TObj(y);

    clocks = clock();
    F = TObj.Quad();
    std::cout << "F = " << F << ". Time of sequential algorithm: " << (clock() - clocks) / CLOCKS_PER_SEC
              << std::endl;

    clocks = clock();
    F = TObj.Concurrent_Quad();
    std::cout << "F = " << F << ". Time of parallel algorithm:" << (clock() - clocks) / CLOCKS_PER_SEC
              << std::endl;

}
