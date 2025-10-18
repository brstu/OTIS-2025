#pragma once
#include <vector>

struct abcd{
    double a;
    double b;
    double c;
    double d;
};
enum class ModelType { linear = 1, nonlinear = 2};

std::vector<double> linear_func(int steps, double a, double b, std::vector<double>& u, double y0, double y1);
std::vector<double> nonlinear_func(int steps, const abcd& srt_fun, std::vector<double>& u, double y0, double y1);