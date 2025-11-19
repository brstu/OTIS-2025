#include <iostream>
#include <vector>
#include <cmath>

class func
{
private:
    double a;
    double b;
    double c;
    double d;
    double t_curr; // Current value of the output/state variable at time step n
    double t_prev; // Previous value of the output/state variable at time step n-1
    double u_curr; // Current value of the input variable at time step n
    double u_prev; // Previous value of the input variable at time step n-1

public:
    func() : a(1), b(1), c(1), d(1), t_curr(1), t_prev(0), u_curr(1), u_prev(0) {}
    func(double a, double b, double c, double d) : a(a), b(b), c(c), d(d), t_curr(1), t_prev(0), u_curr(1), u_prev(0) {}

    void value_set(double tcurr, double tprev, double ucurr, double uprev)
    {
        t_curr = tcurr;
        t_prev = tprev;
        u_curr = ucurr;
        u_prev = uprev;
    }

    std::vector<double> linear(int steps) const
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

    std::vector<double> nonlinear(int steps) const
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
};