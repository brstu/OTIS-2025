#include <cmath>

double linear(double y1, double u1, double a1, double b1)
{
    return a1 * y1 + b1 * u1;
}

double non_linear(double y1, double& y1_p1, double u1, double a1, double b1, double c1, double d1)
{
    y1_p1 = y1;
    return a1 * y1 - b1 * y1_p1 * y1_p1 + c1 * u1 + d1 * std::sin(u1);
}