#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <cmath> 
#include <stdexcept>

struct NonlinearParams {
    double a;
    double b;
    double c;
    double d;
    double u;
    double uPrev;
    double y;
    double yPrev;
};

double nextLinear(double a, double b, double u, double y);

void simulateLinear(double a, double b, double u, int steps);

double nextNonlinear(const NonlinearParams& p);

void simulateNonlinear(double a, double b, double c, double d, double u, int steps);

#endif // MODEL_H