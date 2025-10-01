#include <iostream>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
class func {
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
    func() : a(1), b(1), c(1), d(1) {}
    func(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {}
    void value_set(double t_curr, double t_prev, double u_curr, double u_prev)
    {
        this->t_curr = t_curr;
        this->t_prev = t_prev;
        this->u_curr = u_curr;
        this->u_prev = u_prev;
    }
    vector<double> linear(int steps)
    {
        vector<double> ans(steps);
        ans[0] = t_curr;
        for (int i = 1; i < steps; i++)
        {
            ans[i] = a * ans[i - 1] + b * u_curr;
        }
        return ans;
    }
    vector<double> nonlinear(int steps)
    {
        vector<double> ans(steps);
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
    cin >> steps;
    func Func(0.2, 0.3, 0.4, 0.5);
    Func.value_set(3, 2, 3, 2);
    vector<double> temp(steps);
    temp = Func.linear(steps);
    cout << "Linear::\n";
    for (auto i : temp)
    {
        cout << i << endl;
    }
    temp = Func.nonlinear(steps);
    cout << "Nonlinear::\n";
    for (auto i : temp)
    {
        cout << i << endl;
    }
}