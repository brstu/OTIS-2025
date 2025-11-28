#include "model.h"
#include <cmath>

PlantModel::PlantModel(double a, double b, double c, double d)
    : a(a), b(b), c(c), d(d), t(0.0)
{
}

void PlantModel::setParameters(double na, double nb, double nc, double nd)
{
    this->a = na;
    this->b = nb;
    this->c = nc;
    this->d = nd;
}

void PlantModel::setState(double nt, double nu)
{
    t = nt;
    u = nu;
}

double PlantModel::getOutput() const
{
    return t;
}

double PlantModel::linearStep(double nu)
{
    t = a * t + b * nu;
    return t;
}

double PlantModel::nonlinearStep(double nu)
{
    t = a * t - b * std::pow(t, 2) + c * nu + d * std::sin(nu);
    return t;
}

std::vector<double> PlantModel::linear(int steps) const
{
    if (steps <= 0)
        return {};

    std::vector<double> result(steps);
    double current_t = t;

    for (int i = 0; i < steps; i++)
    {
        result[i] = current_t;
        current_t = a * current_t + b * u;
    }
    return result;
}

std::vector<double> PlantModel::nonlinear(int steps) const
{
    if (steps <= 0)
        return {};

    std::vector<double> result(steps);
    double current_t = t;

    for (int i = 0; i < steps; i++)
    {
        result[i] = current_t;
        current_t = a * current_t - b * std::pow(current_t, 2) + c * u + d * std::sin(u);
    }
    return result;
}