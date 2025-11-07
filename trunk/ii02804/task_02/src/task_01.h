#pragma once

// copilot не разрушал 8 параматров в функции только 7
struct NonLinearParams {
    double a;
    double b;
    double c;
    double d;
};

double linear_model(double y, double u, double a, double b);
double non_linear_model(double y, double& y_prev, double u, double& u_prev, const NonLinearParams& p);
