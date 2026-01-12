#ifndef MODELS_HPP
#define MODELS_HPP

double linear_model(double y, double u, double a, double b);

double nonlinear_model(double y_curr, double y_prev, double u, double u_prev, double a, double b, double c, double d);

#endif