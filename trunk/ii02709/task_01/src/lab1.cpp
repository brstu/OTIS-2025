#include <iostream>
#include <cmath>

const double a = 0.9;
const double b = 0.5;
const double c1 = 0.1;
const double c2 = 0.05;

int main() {
    int steps = 20;
    double y_linear = 20.0;
    double y_nonlinear = 20.0;
    double u = 5.0;
    std::cout << "Step\tlinear\tNonLinear\n";
    for (int t = 0; t < steps; ++t) {
        double next_linear = a * y_linear + b * u;
        double next_nonlinear = a * y_nonlinear + b * u + c1 * u * sin(u) + c2 * u * cos(u);
        std::cout << t << "\t" << next_linear << "\t\t" << next_nonlinear << "\n";
        y_linear = next_linear;
        y_nonlinear = next_nonlinear;
    }
    return 0;
}
