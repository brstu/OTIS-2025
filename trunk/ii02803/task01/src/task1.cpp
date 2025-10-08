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

vector<double> fun2(int n, double a1, double a2, double b1, double b2, double c1, double c2, double d,
                    const vector<double>& u, double y0, double y1) {
    vector<double> y(n + 1);
    y[0] = y0;
    y[1] = y1;

    for (int t = 1; t < n; t++) {
        y[t + 1] = a1 * y[t] + a2 * y[t - 1] + 
                   b1 * u[t] + b2 * u[t - 1] + 
                   c1 * (y[t] * y[t]) + 
                   c2 * sin(u[t]) + d;
    }
    return y;
}

int main() {
    int n; 
    double a, b; 
    double a1, a2, b1, b2, c1, c2, d; 

    cout << "Number of steps n: ";
    cin >> n;

    cout << "Parameters for linear model (a, b): ";
    cin >> a >> b;

    cout << "Parameters for nonlinear model (a1, a2, b1, b2, c1, c2, d): ";
    cin >> a1 >> a2 >> b1 >> b2 >> c1 >> c2 >> d;

    vector<double> u(n + 1);
    cout << "Enter " << n << " values of the input signal u (u[0] to u[" << n-1 << "]):\n";
    for (int i = 0; i < n; i++) {
        cin >> u[i];
    }
    u[n] = 0.0;

    double y0, y1;
    cout << "Initial conditions y0 and y1: ";
    cin >> y0 >> y1;

    auto yLinear = fun1(n, a, b, u, y0);
    auto yNonlinear = fun2(n, a1, a2, b1, b2, c1, c2, d, u, y0, y1);

    cout << "Time\tLinear Model\tNonlinear Model\n";
    cout << fixed;
    cout.precision(4);
    for (int t = 0; t <= n; t++) {
        cout << t << "\t" << yLinear[t] << "\t\t" << yNonlinear[t] << "\n";
    }

    return 0;
}