#pragma once


double linear_model(double y, double u, double a, double b);
double non_linear_model(double y, double& y_prev, double u, double& u_prev, double a, double b, double c, double d);