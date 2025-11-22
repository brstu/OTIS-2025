#pragma once

struct NonLinearParams {
    double a;
    double b;
    double c;
    double d;
};

double linear_model(double y, double u, double a, double b);
double non_linear_model(double y, double& y_prev, double u, double& u_prev, const NonLinearParams& p);
