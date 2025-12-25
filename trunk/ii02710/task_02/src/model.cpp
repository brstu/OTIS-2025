#include "model.h"
#include <cmath>

double linearStep(double a, double b, double u, double y_prev) {
    return a * y_prev + b * u;
}

double nonlinearStep(const NonLinearParams &params,
    double y_curr, double y_prev, double u_curr, double u_prev) {
    return params.a * y_curr - params.b * (y_prev * y_prev) + params.c * u_curr + params.d * std::sin(u_prev);
}