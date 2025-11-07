#include "task_01.h"
#include <cmath>

// Линейная модель
double linear_model(double y, double u, double a, double b) {
    return a * y + b * u;
}

// Нелинейная модель с сохранением u_prev
double non_linear_model(double y, double& y_prev, double u, double& u_prev, double a, double b, double c, double d) {
    y_prev = y;
    double linear_part = a * y + c * u;
    double nonlinear_part = -b * y * y + d * std::sin(u);  // синус берём от текущего u
    double result = linear_part + nonlinear_part;
    u_prev = u;  // обновляем u_prev
    return result;
}
