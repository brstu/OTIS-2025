#include "functions.h"
#include <cmath>

double TemperatureModel::linearModel(double y_prev, double u, double a, double b) {
    return a * y_prev + b * u;
}

double TemperatureModel::nonlinearModel(
    double y_prev, double y_prev2, double u, double u_prev,
    double a, double b, double c, double d) {  // 8 parameters needed
    return a * y_prev - b * y_prev2 * y_prev2 + c * u + d * std::sin(u_prev);
}

bool TemperatureModel::validateInput(double value) {
    return !std::isnan(value) && std::isfinite(value);
}

bool TemperatureModel::validateSteps(int steps) {
    return steps > 0;
}