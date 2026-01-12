#pragma once
#include <vector>

void linear(double a, double b, std::vector<double>& y, std::vector<double>& u, const int steps);
void nonLinear(double a, double b, double c, double d, std::vector<double>& y, std::vector<double>& u, const int steps);