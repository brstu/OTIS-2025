#pragma once
#include <vector>

enum ModelType { linear = 1, nonlinear = 2};

std::vector<double> linear_func(int steps, double a, double b, std::vector<double>& u, double y0, double y1);
std::vector<double> nonlinear_func(int steps, double a, double b, double c, double d, std::vector<double>& u, double y0, double y1);