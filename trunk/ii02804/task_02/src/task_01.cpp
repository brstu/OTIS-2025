#include "task_01.h"
#include <cmath>

// Линейная модель: вычисляет линейную комбинацию входов y и u с коэффициентами a и b (a * y + b * u)
double linear_model(double y, double u, double a, double b) {
    return a * y + b * u;
}

double non_linear_model(double y, double& y_prev, double u, double& u_prev, double a, double b, double c, double d) {
    y_prev = y;  // сохраняем предыдущую величину
    double linear_part = a * y + c * u;       // linear component of the model
    double nonlinear_part = -b * y * y + d * std::sin(u_prev);
    u_prev = u;  // сохраняем предыдущую величину управления
    double result = linear_part + nonlinear_part;
    y_prev = y;  // сохраняем предыдущую величину
    return result;
}
