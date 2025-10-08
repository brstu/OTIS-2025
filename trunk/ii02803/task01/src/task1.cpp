#include <iostream> 
#include <vector>
#include <cmath>

using namespace std;

vector<double> fun1(int n, double a, double b, const vector<double>& u, double y0) {
    vector<double> y(n + 1);
    y[0] = y0;
    for (int t = 0; t < n; t++) {
        y[t + 1] = a * y[t] + b * u[t];
    }
    return y;
}

vector<double> fun2(int n, double a, double b, double c, double d, double e, double f, double g,
                    const vector<double>& u, double y0, double y1) {
    vector<double> y(n + 1);
    y[0] = y0;
    y[1] = y1;

    for (int t = 1; t < n; t++) {
        y[t + 1] = a * y[t] + 
                   b * (y[t - 1] * y[t - 1]) + 
                   c * u[t] + 
                   d * sin(u[t - 1]) + 
                   e * (u[t] * u[t]) + 
                   f * cos(y[t]) + 
                   g;
    }
    return y;
}

int main() {
    int n;
    double a_lin;
    double b_lin;
    double a_nlin;
    double b_nlin;
    double c_nlin;
    double d_nlin;
    double e_nlin;
    double f_nlin;
    double g_nlin;

    cout << "Number of steps n: ";
    cin >> n;

    cout << "Parameters for linear model (a, b): ";
    cin >> a_lin;
    cin >> b_lin;

    cout << "Parameters for nonlinear model (a, b, c, d, e, f, g): ";
    cin >> a_nlin;
    cin >> b_nlin;
    cin >> c_nlin;
    cin >> d_nlin;
    cin >> e_nlin;
    cin >> f_nlin;
    cin >> g_nlin;

    vector<double> u(n + 1);
    cout << "Enter " << n << " values of the input signal u (u[0] to u[" << n-1 << "]):\n";
    for (int i = 0; i < n; i++) {
        cin >> u[i];
    }
    u[n] = 0.0;

    double y0;
    double y1;
    cout << "Initial conditions y0 and y1: ";
    cin >> y0;
    cin >> y1;

    vector<double> yLinear = fun1(n, a_lin, b_lin, u, y0);
    vector<double> yNonlinear = fun2(n, a_nlin, b_nlin, c_nlin, d_nlin, e_nlin, f_nlin, g_nlin, u, y0, y1);

    cout << "Time\tLinear Model\tNonlinear Model\n";
    cout << fixed;
    cout.precision(4);
    for (int t = 0; t <= n; t++) {
        cout << t << "\t" << yLinear[t] << "\t\t" << yNonlinear[t] << "\n";
    }

    return 0;
}