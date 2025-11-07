#include "task_01.h"
#include <cmath>

double linear_model_ii02804(double y, double u, double a, double b) {
    double result = a * y + b * u;
    return result;
}

double non_linear_model_ii02804(double y, double& y_previous, double u, double& u_previous, double a, double b, double c, double d) {
    y_previous = y;
    double linear_part = a * y + c * u;
    double nonlinear_part = -b * y * y + d * std::sin(u_previous);
    u_previous = u;
    double final_result = linear_part + nonlinear_part;
    return final_result;
}
