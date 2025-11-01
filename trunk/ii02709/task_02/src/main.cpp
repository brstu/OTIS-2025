#include <iostream>
#include <vector>
#include "lab2.h"

int main() {
    int steps = 20;
    long double y0 = 1.5L;
    long double u = 2.0L;

    auto linear_values = lab2::simulate_linear(steps, y0, u);
    auto nonlinear_values = lab2::simulate_nonlinear(steps, y0, u);

    std::cout << "Step\tLinear\t\tNonLinear\n";
    for (int t = 0; t < steps; ++t) {
        std::cout << t << "\t" 
                  << linear_values[t] << "\t"
                  << nonlinear_values[t] << "\n";
    }
    return 0;
}