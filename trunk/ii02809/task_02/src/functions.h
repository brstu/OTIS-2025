#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct ModelParams {
    double a;
    double b;
    double c;
    double d;
};

double linearModel(double y_tau, double u_tau, const ModelParams& params);
double nonlinearModel(double y_tau, double y_tau_minus_1, double u_tau, double u_tau_minus_1, const ModelParams& params);

#endif
