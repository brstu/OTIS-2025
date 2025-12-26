#include "functions.h"
#include <iostream>
#include <cmath>
#include <vector>

void linear(double a, double b, std::vector<double>& y, const int steps, double target)
{
	double u;
	double P = 1.6;
	double I = 0.32;
	double D = 0.4;
	double e = 0;
	double e0;
	double sumE = 0;
	double dE;
	double er = 0;

	for (int i = 1; i < steps; i++)
	{
		e0 = e;
		e = target - y[i - 1];
		sumE += e;
		dE = e - e0;
		u = P * e + I * sumE + D * dE;
		y[i] = a * y[i - 1] + b * u;
		std::cout << "y[" << i << "] = " << y[i] << std::endl;
		er = fabs(y[i] - target);
		std::cout << "Error of value: " << er << std::endl << std::endl;
	}
}