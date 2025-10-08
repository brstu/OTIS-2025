#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// --- Структуры параметров ---
struct LinearParams {
    double a;
    double b;
};

struct NonlinearParams {
    double a;
    double b;
    double c;
    double d;
    double e;
    double f;
    double g;
};

// --- Линейная модель ---
vector<double> fun1(int n, const LinearParams& p, const vector<double>& u, double y0) {
    vector<double> y(n + 1);
    y[0] = y0;
    for (int t = 0; t < n; t++) {
        y[t + 1] = p.a * y[t] + p.b * u[t];
    }
    return y;
}

// --- Нелинейная модель ---
vector<double> fun2(int n, const NonlinearParams& p, const vector<double>& u, double y0, double y1) {
    vector<double> y(n + 1);
    y[0] = y0;
    y[1] = y1;

    for (int t = 1; t < n; t++) {
        double current_y = y[t];
        double previous_y = y[t - 1];
        double previous_previous_y = (t >= 2) ? y[t - 2] : y0;
        double current_u = u[t];
        double previous_u = u[t - 1];

        y[t + 1] = p.a * current_y +
                   p.b * previous_y * previous_y +
                   p.c * current_u +
                   p.d * sin(previous_u) +
                   p.e * previous_u * previous_u +
                   p.f * previous_previous_y +
                   p.g;
    }
    return y;
}

// --- Главная функция ---
int main() {
    int n;
    LinearParams lin;
    NonlinearParams nlin;

    cout << "Number of steps n: ";
    cin >> n;

    cout << "Parameters for linear model (a, b): ";
    cin >> lin.a >> lin.b;

    cout << "Parameters for nonlinear model (a, b, c, d, e, f, g): ";
    cin >> nlin.a >> nlin.b >> nlin.c >> nlin.d >> nlin.e >> nlin.f >> nlin.g;

    vector<double> u(n + 1);
    cout << "Enter " << n << " values of the input signal u (u[0] to u[" << n - 1 << "]):\n";
    for (int i = 0; i < n; i++) {
        cin >> u[i];
    }
    u[n] = 0.0;

    double y0, y1;
    cout << "Initial conditions y0 and y1: ";
    cin >> y0 >> y1;

    vector<double> yLinear = fun1(n, lin, u, y0);
    vector<double> yNonlinear = fun2(n, nlin, u, y0, y1);

    cout << "\nTime\tLinear Model\tNonlinear Model\n";
    cout << fixed;
    cout.precision(4);
    for (int t = 0; t <= n; t++) {
        cout << t << "\t" << yLinear[t] << "\t\t" << yNonlinear[t] << "\n";
    }

    return 0;
}
