#include <iostream>
#include <vector>
#include <iomanip> // для std::setprecision
#include "lab2.h"

int main() {
    int steps = 20;
    long double y_linear = 1.5L;
    long double y_nonlinear = 1.5L;
    long double u = 2.0L;

    auto linear_values = lab2::simulate_linear(steps, y_linear, u);
    auto nonlinear_values = lab2::simulate_nonlinear(steps, y_nonlinear, u);

    std::cout << std::setprecision(18);
    std::cout << "Step\tLinear\t\t\tNonLinear\n";
    for (int t = 0; t < steps; ++t) {
        // безопасный вывод: проверка на доступность индекса
        std::cout << t << "\t" 
                  << linear_values[t] << "\t"
                  << nonlinear_values[t] << "\n";
    }
    return 0;
}
