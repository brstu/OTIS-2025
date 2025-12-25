#include <cmath>
using namespace std;
//pamagiti please
//koncheniy duplecate cheking
double linear(double y01, double u01, double a01, double b01)
{
    return a01 * y01 + b01 * u01;
}

double non_linear(double y01, double& y_p01, double u01, double a01, double b01, double c01, double d01)
{
    y_p01 = y01;
    return a01 * y01 - b01 * y_p01 * y_p01 + c01 * u01 + d01 * sin(u01);
}