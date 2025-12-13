#include "model.h"
#include <cmath>

double linearStep(double a, double b, double u, double y_prev) {
    return a * y_prev + b * u;
}

double nonlinearStep(double a, double b, double c, double d,
    double y_curr, double y_prev, double u_curr, double u_prev) {
    return a * y_curr - b * (y_prev * y_prev) + c * u_curr + d * std::sin(u_prev);
}