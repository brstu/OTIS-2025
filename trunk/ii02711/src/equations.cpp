#include <cmath>
#include "equations.h"

double Nonlinear(double a, double b, double c, double d, double y_prev, double u, double u_prev, double& y_next, double y) {
	y_next = a * y - b * (y_prev * y_prev) + c * u + d * sin(u_prev);
	return y_next;
}
double Linear(double a, double b, double y, double& y_next, double u) {
	y_next = a * y + b * u;
	return y_next;
}