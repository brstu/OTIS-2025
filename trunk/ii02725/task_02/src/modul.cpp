#include "module.h"
#include <cmath>

void calculate_linear_model(
        int nSteps,
        double aCoef,
        double bCoef,
        const std::vector<double>& u,
        std::vector<double>& y
)
{
    for (int i = 0; i < nSteps; ++i)
    {
        double prevValue = y[i];
        double inputValue = u[i];
        y[i + 1] = aCoef * prevValue + bCoef * inputValue;
    }
}

void calculate_nonlinear_model(
        int total,
        double alpha,
        double beta,
        double gamma,
        double delta,
        const std::vector<double>& u,
        std::vector<double>& y
)
{
    for (int i = 1; i < total; ++i)
    {
        double yt = y[i];
        double ym1 = y[i - 1];

        double ut = u[i];
        double um1 = u[i - 1];

        double part1 = alpha * yt;
        double part2 = beta * ym1 * ym1;
        double part3 = gamma * ut;
        double part4 = delta * std::sin(um1);

        y[i + 1] = part1 - part2 + part3 + part4;
    }
}