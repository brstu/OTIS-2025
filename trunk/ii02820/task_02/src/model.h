#ifndef MODEL_H
#define MODEL_H

double linear(double y, double u, double a, double b);
double non_linear(double y_current, double y_prev, double u_current, double a, double b, double c, double d);

#endif