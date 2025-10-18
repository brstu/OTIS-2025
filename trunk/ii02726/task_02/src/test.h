#pragma once
#include <vector>

struct abcd{
    double a, b, c, d;
};
enum class ModelType { linear = 1, nonlinear = 2};

std::vector<double> linear_func(int steps, double a, double b, std::vector<double>& u, double y0, double y1);
std::vector<double> nonlinear_func(int steps, abcd srt_fun, std::vector<double>& u, double y0, double y1);