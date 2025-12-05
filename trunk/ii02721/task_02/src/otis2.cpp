#include <iostream>
#include <cmath>
#include "n_linear.h"

int main() {
    double temp_now = 0;
    double temp_prev = 0;
    double temp_next = 0;
    double heat_now = 0;
    double heat_prev = 0;
    double A;
    double B;
    double C;
    double D;
    std::cout << "Enter start temp(y) & temp(u): ";
    std::cin >> temp_now >> heat_now;

    std::cout << "Enter A, B, C, D: ";
    std::cin >> A >> B >> C >> D;

    temp_prev = temp_now;

    std::cout << "\nLinear model\n";
    temp_now = linear(A, B, temp_prev, heat_now);
    std::cout << "Temperature = " << temp_now << std::endl;
    temp_prev = temp_now;
    std::cout << "\nNonlinear model\n";
    Nonl l;
    l.A = A;
    l.B = B;
    l.C = C;
    l.D = D;
    l.heat_prev = 0;
    l.temp_now = temp_prev;
    l.temp_prev = temp_now;
    l.heat_prev = heat_now;
    temp_now = nonlinear(l);
    std::cout << "Temperature = " << temp_now << std::endl;

    return 0;
}