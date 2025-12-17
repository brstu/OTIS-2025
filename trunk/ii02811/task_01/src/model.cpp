#include "main.h"
#include <cmath>

using namespace std;

double x(double y, double u, double a, double b) {
    return a * y + b * u;
}

double x1(double y, double u, double a, double b, double c, double d, double yx) {
    return a * y - b * y * yx + c * u + d * sin(u);
}