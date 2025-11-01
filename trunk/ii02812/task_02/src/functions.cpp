#include "functions.h"
#include <cmath>

double linear_model(double a, double b, double y_prev, double u) {
    return a * y_prev + b * u;
}

double nonlinear_model(double a, double b, double c, double d,
    double y0, double y1, double u) {
    return a * y1 - b * std::pow(y0, 2) + c * u + d * std::sin(u);
}
