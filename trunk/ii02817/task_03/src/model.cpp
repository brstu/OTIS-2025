#include "model.h"

PlantModel::PlantModel(double a, double b, double c, double d)
    : a(a), b(b), c(c), d(d)
{
}

void PlantModel::setParameters(double na, double nb, double nc, double nd)
{
    this->a = na;
    this->b = nb;
    this->c = nc;
    this->d = nd;
}

void PlantModel::setState(double ntcurr, double ntprev, double nucurr, double nuprev)
{
    t_curr = ntcurr;
    t_prev = ntprev;
    u_curr = nucurr;
    u_prev = nuprev;
}

double PlantModel::getOutput() const
{
    return t_curr;
}

double PlantModel::linearStep(double u)
{
    double new_t = a * t_curr + b * u;
    t_prev = t_curr;
    t_curr = new_t;
    u_prev = u_curr;
    u_curr = u;
    return new_t;
}

double PlantModel::nonlinearStep(double u)
{
    double new_t = a * t_curr - b * std::pow(t_prev, 2) + c * u + d * std::sin(u_prev);
    t_prev = t_curr;
    t_curr = new_t;
    u_prev = u_curr;
    u_curr = u;
    return new_t;
}

std::vector<double> PlantModel::linear(int steps) const
{
    if (steps <= 0)
        return {};

    std::vector<double> ans(steps);
    ans[0] = t_curr;
    for (int i = 1; i < steps; i++)
    {
        ans[i] = a * ans[i - 1] + b * u_curr;
    }
    return ans;
}

std::vector<double> PlantModel::nonlinear(int steps) const
{
    if (steps <= 0)
        return {};

    std::vector<double> ans(steps);
    if (steps >= 1)
    {
        ans[0] = t_prev;
    }
    if (steps >= 2)
    {
        ans[1] = t_curr;
    }
    for (int i = 2; i < steps; i++)
    {
        ans[i] = a * ans[i - 1] - b * std::pow(ans[i - 2], 2) + c * u_curr + d * std::sin(u_prev);
    }
    return ans;
}