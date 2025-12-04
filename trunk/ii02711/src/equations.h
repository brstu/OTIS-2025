#ifndef EQUAT_H
#define EQUAT_H
#include <cmath>

double Nonlinear(double a, double b, double c, double d, double y_prev, double u, double u_prev, double& y_next, double y);
double Linear(double a, double b, double y, double& y_next, double u);

#endif 
