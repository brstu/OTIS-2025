#include "functions.h"
#include <iostream>
#include <cmath>

void linear(double a, double b, std::vector<double>& y, std::vector<double>& u, const int steps)
{
	for (int i = 1; i < steps; i++)
	{
		y[i] = a * y[i - 1] + b * u[i - 1];
		u[i] = u[i - 1] * 0.8; //Коэффициент понижения температуры объекта
		std::cout << "y[" << i << "] = " << y[i] << std::endl;
	}
}

void nonLinear(double a, double b, double c, double d, std::vector<double>& y, std::vector<double>& u, const int steps)
{
	for (int i = 1; i < steps - 1; i++)
	{
		y[i + 1] = a * y[i] - b * y[i - 1] / 2.0 + c * u[i] + d * sin(u[i - 1]);
		u[i + 1] = u[i] * 0.8; //Коэффициент понижения температуры объекта
		std::cout << "y[" << i << "] = " << y[i] << std::endl;
	}

}