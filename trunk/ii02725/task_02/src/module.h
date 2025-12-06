#ifndef MODULE_H
#define MODULE_H

#include <vector>

constexpr int MAXIMUM_STEPS = 101;

void calculate_linear_model(
        int nSteps,
        double aCoef,
        double bCoef,
        const std::vector<double>& u,
        std::vector<double>& y
);

void calculate_nonlinear_model(
        int numberOfSteps,
        double a,
        double b,
        double c,
        double d,
        const std::vector<double>& u,
        std::vector<double>& y
);

#endif