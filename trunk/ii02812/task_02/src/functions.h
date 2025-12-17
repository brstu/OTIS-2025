#pragma once
#include <cmath>

double linear_model(double a, double b, double y_prev, double u);

double nonlinear_model(double a, double b, double c, double d, double y0, double y1, double u, double u_prev);
