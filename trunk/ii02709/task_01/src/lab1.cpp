#include <iostream>
#include <vector>
#include <cmath>

const long double a = 0.9;
const long double b = 0.5;
const long double c1 = 0.1;
const long double c2 = 0.05;

int main() {
    int steps = 20;
    long double y_linear = 1.5;
    long double y_nonlinear = 1.5;
    long double u = 2.0;

    std::vector<long double> linear_values;
    std::vector<long double> nonlinear_values;

    linear_values.reserve(steps);
    nonlinear_values.reserve(steps);

    for (int t = 0; t < steps; ++t) {
        long double next_linear = a * y_linear + b * u;
        long double next_nonlinear = a * y_nonlinear - b * y_nonlinear * y_nonlinear + c1 * u + c2 * std::sinh(u);
        linear_values.push_back(next_linear);
        nonlinear_values.push_back(next_nonlinear);

        y_linear = next_linear;
        y_nonlinear = next_nonlinear;
    }

    std::cout.precision(18);
    std::cout << "Step\tLinear\t\t\tNonLinear\n";
    for (int t = 0; t < steps; ++t) {
        std::cout << t << "\t"
                  << linear_values[t] << "\t"
                  << nonlinear_values[t] << "\n";
    }

    return 0;
}
