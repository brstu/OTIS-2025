#ifndef MODEL_H
#define MODEL_H

struct NonlinearParams {
    double a;
    double b;
    double c;
    double d;
};

double nextLinear(double a, double b, double u, double y);
void simulateLinear(double a, double b, double u, int steps);
double nextNonlinear(const NonlinearParams& params, double u_prev, double y, double y_prev);
void simulateNonlinear(double a, double b, double c, double d, double u, int steps);

#endif