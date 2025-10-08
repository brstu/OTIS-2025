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
vector<double> fun1(int n,
                    const LinearParams& p,
                    const vector<double>& u,
                    double y0)
{
    vector<double> y(n + 1);
    y[0] = y0;

    for (int t = 0; t < n; t++) {
        double yt_next = p.a * y[t] + p.b * u[t];
        y[t + 1] = yt_next;
    }

    return y;
}

// --- Нелинейная модель ---
vector<double> fun2(int n,
                    const NonlinearParams& p,
                    const vector<double>& u,
                    double y0,
                    double y1)
{
    vector<double> y(n + 1);
    y[0] = y0;
    y[1] = y1;

    for (int t = 1; t < n; t++) {
        double current_y = y[t];
        double previous_y = y[t - 1];
        double previous_previous_y;

        if (t >= 2) {
            previous_previous_y = y[t - 2];
        } else {
            previous_previous_y = y0;
        }

        double current_u = u[t];
        double previous_u = u[t - 1];

        double squared_previous_y = previous_y * previous_y;
        double squared_previous_u = previous_u * previous_u;
        double sin_previous_u = sin(previous_u);

        double yt_next = p.a * current_y
                       + p.b * squared_previous_y
                       + p.c * current_u
                       + p.d * sin_previous_u
                       + p.e * squared_previous_u
                       + p.f * previous_previous_y
                       + p.g;

        y[t + 1] = yt_next;
    }

    return y;
}

int main() {
    int n;
    cout << "Number of steps n: ";
    cin >> n;

    LinearParams lin;
    cout << "Parameter a (linear model): ";
    cin >> lin.a;
    cout << "Parameter b (linear model): ";
    cin >> lin.b;

    NonlinearParams nlin;
    cout << "Parameter a (nonlinear model): ";
    cin >> nlin.a;
    cout << "Parameter b (nonlinear model): ";
    cin >> nlin.b;
    cout << "Parameter c (nonlinear model): ";
    cin >> nlin.c;
    cout << "Parameter d (nonlinear model): ";
    cin >> nlin.d;
    cout << "Parameter e (nonlinear model): ";
    cin >> nlin.e;
    cout << "Parameter f (nonlinear model): ";
    cin >> nlin.f;
    cout << "Parameter g (nonlinear model): ";
    cin >> nlin.g;

    vector<double> u(n + 1);
    cout << "Enter " << n << " values of the input signal u (u[0] to u[" << n - 1 << "]):\n";
    for (int i = 0; i < n; i++) {
        cin >> u[i];
    }

    double y0;
    cout << "Initial condition y0: ";
    cin >> y0;
    double y1;
    cout << "Initial condition y1: ";
    cin >> y1;

    u[n] = y0;

    vector<double> yLinear = fun1(n, lin, u, y0);
    vector<double> yNonlinear = fun2(n, nlin, u, y0, y1);

    cout << "\nAfter the final input, u[n] is set equal to y0 for consistency.\n";
    cout << "Time\tLinear Model\tNonlinear Model\n";
    cout << fixed;
    cout.precision(4);

    for (int t = 0; t <= n; t++) {
        cout << t << "\t" << yLinear[t] << "\t\t" << yNonlinear[t] << "\n";
    }

    return 0;
}
