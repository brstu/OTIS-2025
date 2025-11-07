#include "task_01.h"
#include <cmath>

// Линейная модель
double linear_model(double y, double u, double a, double b) {
    return a * y + b * u;
}

double non_linear_model(double y, double& y_prev, double u, double& u_prev, double a, double b, double c, double d) {
    y_prev = y;  
    double linear_part = a * y + c * u;       
    double nonlinear_part = -b * y * y + d * std::sin(u_prev);
    u_prev = u;  
    double result = linear_part + nonlinear_part;
    y_prev = y;  
    return result;
}
