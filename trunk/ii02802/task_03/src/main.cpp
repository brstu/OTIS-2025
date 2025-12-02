#include <iostream>
#include "function.h"

int main() {
    double K = 10.0;
    double T = 0.1;
    double TD = 0.05;
    double T0 = 1.0;
    double tau = 10.0;
    double K_obj = 1.0;

    PID pid(K, T, TD, T0);
    Object obj(tau, K_obj, T0);

    double w = 1.0;
    double y = 0.0;
    double u = 0.0;

    for (int k = 0; k < 200; ++k) {
        if (k == 100) w = 2.0;
        double e = w - y;
        u = pid.compute(e);
        y = obj.update(u);
        std::cout << "k=" << k << ", w=" << w << ", y=" << y << ", u=" << u << std::endl;
    }

    return 0;
}