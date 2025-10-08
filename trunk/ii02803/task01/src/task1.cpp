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

    // Начинаем с t=2, чтобы избежать обращения к u[-1]
    for (int t = 2; t <= n; t++) {
        // Используем u[t-1] и u[t-2] для соответствия временным шагам
        y[t] = a * y[t - 1] - b * (y[t - 2] * y[t - 2]) + c * u[t - 1] + d * sin(u[t - 2]);
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

    // Создаем вектор u размером n+1, чтобы иметь запас для u[-1]
    vector<double> u(n + 1);
    cout << "Enter " << n << " values of the input signal u (u[0] to u[" << n-1 << "]):\n";
    for (int i = 0; i < n; i++) {
        cin >> u[i];
    }
    // Для u[n] можно установить значение по умолчанию (например, 0)
    u[n] = 0.0;

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