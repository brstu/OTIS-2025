#include <iostream>
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
    double t_curr;
    double t_prev;
    double u_curr;
    double u_prev;

public:
    func() : a(1), b(1), c(1), d(1), t_curr(1), t_prev(0), u_curr(1), u_prev(0) {}
    func(double a, double b, double c, double d) : a(a), b(b), c(c), d(d), t_curr(3), t_prev(2), u_curr(3), u_prev(2) {}
    void value_set(double tcurr, double tprev, double ucurr, double uprev)
    {
        t_curr = tcurr;
        t_prev = tprev;
        u_curr = ucurr;
        u_prev = uprev;
    }
    std::vector<double> linear(int steps) const
    {
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
        std::vector<double> ans(steps);
        ans[0] = t_prev;
        ans[1] = t_curr;
        for (int i = 2; i < steps; i++)
        {
            ans[i] = a * ans[i - 1] - b * pow(ans[i - 2], 2) + c * u_curr + d * sin(u_prev);
        }
        return ans;
    }
};

int main()
{
    int steps;
    std::cin >> steps;
    func Func(0.2, 0.3, 0.4, 0.5);
    Func.value_set(3, 2, 3, 2);
    std::vector<double> temp(steps);
    temp = Func.linear(steps);
    std::cout << "Linear::\n";
    for (auto i : temp)
    {
        std::cout << i << std::endl;
    }
    temp = Func.nonlinear(steps);
    std::cout << "Nonlinear::\n";
    for (auto i : temp)
    {
        std::cout << i << std::endl;
    }
}