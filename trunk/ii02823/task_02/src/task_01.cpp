#include <cmath>

double linear(double y, double u, double a, double b)
{
    return a * y + b * u;
}

double non_linear(double y, double& y_p, double u, double a, double b, double c, double d)
{
    y_p = y;
    return a * y - b * y_p * y_p + c * u + d * std::sin(u);
}