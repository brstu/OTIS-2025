#include "model.h"

std::vector<double> simulateLinear(
    int steps,
    double y_init,
    double a,
    double b,
    const std::vector<double>& u
) {
    if (steps <= 0 || u.empty())
        return {};

    std::vector<double> y(steps);
    y[0] = y_init;

    for (int t = 1; t < steps; ++t)
        y[t] = a * y[t - 1] + b * u[t - 1];

    return y;
}

std::vector<double> simulateNonlinear(
    int steps,
    double y_init,
    double a,
    double b,
    double c,
    double d,
    const std::vector<double>& u
) {
    if (steps <= 0)
        return {};

    std::vector<double> y(steps);
    y[0] = y_init;

    if (steps > 1)
        y[1] = a * y[0] + c * u[0];

    for (int t = 2; t < steps; ++t) {
        y[t] = a * y[t - 1]
             - b * std::pow(y[t - 2], 2)
             + c * u[t - 1]
             + d * std::sin(u[t - 2]);
    }

    return y;
}
