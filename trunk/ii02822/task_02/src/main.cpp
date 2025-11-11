#include <iostream>
#include <cmath>
#include "functions.h"

int main() {
    double u_current, u_prev, y, a, b, c, d;
    int count_steps;

    std::cout << "Enter initial temperature y: ";
    if (!(std::cin >> y) || !TemperatureModel::validateInput(y)) {
        std::cerr << "Error: Invalid input for y" << std::endl;
        return 1;
    }

    std::cout << "Enter initial heat u: ";
    if (!(std::cin >> u_current) || !TemperatureModel::validateInput(u_current)) {
        std::cerr << "Error: Invalid input for u" << std::endl;
        return 1;
    }

    u_prev = u_current;

    std::cout << "Enter constants a, b, c, d: ";
    if (!(std::cin >> a >> b >> c >> d)) {
        std::cerr << "Error: Invalid input for constants" << std::endl;
        return 1;
    }

    std::cout << "Enter number of steps: ";
    if (!(std::cin >> count_steps) || !TemperatureModel::validateSteps(count_steps)) {
        std::cerr << "Error: Invalid number of steps" << std::endl;
        return 1;
    }


    double y_linear = y;
    double y_nonlinear_prev = y;
    double y_nonlinear = y;

    std::cout << "\nSimulation results:" << std::endl;

    for (int i = 0; i < count_steps; i++) {
        double y_linear_next = TemperatureModel::linearModel(y_linear, u_current, a, b);
        double y_nonlinear_next = TemperatureModel::nonlinearModel(y_nonlinear, y_nonlinear_prev, u_current, u_prev, a, b, c, d);

        std::cout << "Step " << i + 1 << ":" << std::endl;
        std::cout << "  Linear model: y = " << y_linear_next << std::endl;
        std::cout << "  Nonlinear model: y = " << y_nonlinear_next << std::endl;

        y_linear = y_linear_next;
        y_nonlinear_prev = y_nonlinear;
        y_nonlinear = y_nonlinear_next;
        u_prev = u_current;
    }

    return 0;
}