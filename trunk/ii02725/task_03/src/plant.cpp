#include "plant.h"
#include <cmath>

LinearPlant::LinearPlant(double aa, double bb, double cc, double y0)
    : a(aa), b(bb), c(cc), yk(y0)
{
}

double LinearPlant::step(double u) {
    yk = a * yk + b * u + c;
    return yk;
}

void LinearPlant::reset() {
    yk = 0.0;
}

NonlinearPlant::NonlinearPlant(double aa, double bb, double cc, double al, double y0)
    : a(aa), b(bb), c(cc), alpha(al), yk(y0)
{
}

double NonlinearPlant::step(double u) {
    const double limited = u / (1.0 + alpha * std::fabs(u));
    yk = a * yk + b * limited + c;
    return yk;
}

void NonlinearPlant::reset() {
    yk = 0.0;
}