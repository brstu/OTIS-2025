#include "model.h"
#include <iostream>

int main() {
    double a1 = 0.3;
    double b1 = 0.3;
    double u1 = 0.9;
    int n1 = 10;
    simulateLinear(a1, b1, u1, n1);
    std::cout << std::endl;

    double a2 = 0.1;
    double b2 = 0.2;
    double c2 = 0.4;
    double d2 = 0.2;
    double u2 = 0.8;
    int n2 = 10;
    simulateNonlinear(a2, b2, c2, d2, u2, n2);

    return 0;
}