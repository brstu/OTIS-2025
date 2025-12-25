#include <cmath>

double linear(double y01, double u01, double a01, double b01)
{
    return a01 * y01 + b01 * u01;
}

double non_linear(double y01, double& y01_p01, double u01, double a01, double b01, double c01, double d01)
{
    y01_p01 = y01;
    return a01 * y01 - b01 * y01_p01 * y01_p01 + c01 * u01 + d01 * std::sin(u01);
}