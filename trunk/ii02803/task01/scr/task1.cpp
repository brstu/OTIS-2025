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

vector<double> fun2(int n, double a, double b, double c, double d,
                                 const vector<double>& u, double y0, double y1) {
    vector<double> y(n + 1);
    y[0] = y0;
    y[1] = y1;

    for (int t = 1; t < n; t++) {
        y[t + 1] = a * y[t] - b * (y[t - 1] * y[t - 1]) + c * u[t] + d * sin(u[t - 1]);
    }
    return y;
}

int main() {
    int n; 
    double a, b, c, d;

    cout << "Number of steps n: ";
    cin >> n;

    cout << "a, b, c, d: ";
    cin >> a >> b >> c >> d;

    vector<double> u(n);
    cout << "Enter " << n << " values of the input signal u:\n";
    for (int i = 0; i < n; i++) {
        cin >> u[i];
    }

    double y0, y1;
    cout << "Initial conditions y0 and y1: ";
    cin >> y0 >> y1;

    auto yLinear = fun1(n, a, b, u, y0);
    auto yNonlinear = fun2(n, a, b, c, d, u, y0, y1);

    cout << "Time\tLinear Model\tNonlinear Model\n";
    for (int t = 0; t <= n; t++) {
        cout << t << "\t" << yLinear[t] << "\t\t" << yNonlinear[t] << "\n";
    }

    return 0;
}
