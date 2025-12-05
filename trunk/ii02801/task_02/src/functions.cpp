#include <cmath>
#include <vector>
#include "functions.h"

const double a1 = 0.9;
const double b = 0.1;
const double c = 0.05;
const double d = 0.02;

std::vector<double> simulateLinearfunc(int steps, double y_init, const std::vector<double>& u) {
    if (steps <= 0 || u.empty()) {
        return std::vector<double>();
    } else if (steps == 1) {
        return std::vector<double>(1, y_init);
    }

    if (u.size() < static_cast<size_t>(steps - 1)) {
        return std::vector<double>();
    }

    std::vector<double> y(steps);
    y[0] = y_init;

    for (int t = 1; t < steps; ++t) {
        y[t] = a1 * y[t - 1] + b * u[t - 1];
    }

    return y;
}

std::vector<double> simulateNonlinearfunc(int steps, double y_init, const std::vector<double>& u) {
    if (steps == 0) {
        return std::vector<double>();
    } else if (steps == 1) {
        return std::vector<double>(1, y_init);
    }

    std::vector<double> y(steps);
    y[0] = y_init;
    y[1] = a1 * y[0] + b * u[0];

    for (int t = 2; t < steps; ++t) {
        y[t] = a1 * y[t - 1] - b * std::pow(y[t - 2], 2) + c * u[t - 1] + d * std::sin(u[t - 2]);
    }

    return y;
}
