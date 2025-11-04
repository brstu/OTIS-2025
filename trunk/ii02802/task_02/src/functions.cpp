#include <cmath>
#include "functions.h"

double linear(double y, double u, double a, double b)
{
    return a * y + b * u;
}

double nonlinear(double y, double u, double a, double b, double c, double d)
{
    return a * y - b * y * y + c * u + d * sin(u);
}
