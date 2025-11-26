#include <iostream>
#include <cmath>
#include <vector>

const double a = 0.9;
const double b = 0.1;
const double c = 0.05;
const double d = 0.02;

const double y0_value = 20.0;  
const double C = 1.0;

std::vector<double> simulateLinear(int steps, double y_init, const std::vector<double>& u) {
    if (steps <= 0 || u.empty()) {
        // No steps or empty input vector, return empty vector
        return std::vector<double>();
    } else if (steps == 1) {
        // Only initial value
        return std::vector<double>(1, y_init);
    }
    // Ensure u has enough elements
    if (u.size() < static_cast<size_t>(steps - 1)) {
        // Not enough input values, return empty vector
        return std::vector<double>();
    }
    std::vector<double> y(steps);
    y[0] = y_init;

    for (int t = 1; t < steps; ++t) {
        y[t] = a * y[t - 1] + b * u[t - 1];
    }

    return y;
}

std::vector<double> simulateNonlinear(int steps, double y_init, const std::vector<double>& u) {
    if (steps == 0) {
        // No steps, return empty vector
        return std::vector<double>();
    } else if (steps == 1) {
        // Only initial value
        return std::vector<double>(1, y_init);
    }
    std::vector<double> y(steps);
    y[0] = y_init;
    y[1] = a * y[0] + b * u[0];
    for (int t = 2; t < steps; ++t) {
        y[t] = a * y[t - 1] - b * std::pow(y[t - 2], 2) + c * u[t - 1] + d * std::sin(u[t - 2]);
    }

    return y;
}

int main() {
    int steps = 20;
    double y_init = 25.0;

    std::vector<double> u(steps, 5.0);

    auto y_linear = simulateLinear(steps, y_init, u);
    auto y_nonlinear = simulateNonlinear(steps, y_init, u);

    std::cout << "Time\tLinear\tNonlinear\n";
    for (int t = 0; t < steps; ++t) {
        std::cout << t << "\t" << y_linear[t] << "\t" << y_nonlinear[t] << "\n";
    }

    return 0;
}
