#include <iostream>
#include <cmath>
#include "functions.h"

int main() {
    double u;
    double y;
    double a; 
    double b; 
    double c; 
    double d;
    int steps;

    std::cout << "Enter initial temperature (y): ";
    std::cin >> y;

    std::cout << "Enter initial heat (u): ";
    std::cin >> u;

    std::cout << "Enter coefficients a b c d: ";
    std::cin >> a >> b >> c >> d;

    std::cout << "Enter number of steps: ";
    std::cin >> steps;

    if (steps <= 0) {
        std::cerr << "Error: Number of steps must be positive" << std::endl;
        return 1;
    }
    double y_linear = y;
    double y_nonlinear = y;
    double y_prev = y;

    std::cout << "\nSimulation Results:" << std::endl;
    std::cout << "Step\tLinear Model\tNonlinear Model" << std::endl;

    for (int i = 0; i < steps; i++) {
        y_linear = linear(y_linear, u, a, b);
        double y_temp = non_linear(y_nonlinear, y_prev, u, a, b, c, d);

        y_prev = y_nonlinear;
        y_nonlinear = y_temp;

        std::cout << i + 1 << "\t" << y_linear << "\t" << y_nonlinear << std::endl;
    }
    return 0;
}