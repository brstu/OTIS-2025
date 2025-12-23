#include "n_linear.h"
#include <iostream>
#include <cmath>

double linear(double A, double B, double temp_prev, double heat_now) {
	return A * temp_prev + B * heat_now;
}
double nonlinear(const Nonl& l) {
	return  l.A * l.temp_now - l.B * std::pow(l.temp_prev, 2) + l.C * l.heat_now + l.D * std::sin(l.heat_prev);
}
