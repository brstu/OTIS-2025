#include "task_01.h"
#include <cmath>

double linear_model(double y, double u, double a, double b) {
    return a * y + b * u;
}

double non_linear_model(double y, double& y_prev, double u, double& u_prev, const NonLinearParams& p) {
    y_prev = y;
    double linear_part = p.a * y + p.c * u;
    double nonlinear_part = -p.b * y * y + p.d * std::sin(u);
    u_prev = u;
    return linear_part + nonlinear_part;
}
