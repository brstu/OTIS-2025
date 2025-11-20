#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Линейная модель: y(t+1) = a * y(t) + b * u(t)
vector<double> linearModel(double a, double b, double y0,
                          const vector<double>& u, int timeSteps) {
    vector<double> y(timeSteps);
    y[0] = y0;

    for (int t = 0; t < timeSteps - 1; t++) {
        y[t+1] = a * y[t] + b * u[t];
    }
    return y;
}

// Нелинейная модель: y(t+1) = a * y(t) - b * y(t-1)^2 + c * u(t) + d * sin(u(t-1))
vector<double> nonlinearModel(double a, double b, double c, double d,
                             double y0, const vector<double>& u, int timeSteps) {
    vector<double> y(timeSteps);
    y[0] = y0;

    // Для t=0 используем начальное условие
    if (timeSteps > 1) {
        y[1] = a * y[0] + c * u[0];  // первый шаг без y(t-1)
    }

    for (int t = 1; t < timeSteps - 1; t++) {
        y[t+1] = a * y[t] - b * y[t-1] * y[t-1] + c * u[t] + d * sin(u[t-1]);
    }
    return y;
}

int main() {
    // Параметры модели
    double a = 0.8, b_linear = 0.5, b_nonlinear = 0.1, c = 0.3, d = 0.2;
    double y0 = 20.0;  // начальная температура
    int timeSteps = 10;

    // Входной сигнал (управление)
    vector<double> u(timeSteps, 1.0);  // постоянный сигнал

    cout << "=== Моделирование температуры объекта ===" << endl;
    cout << "Параметры: a=" << a << ", b_linear=" << b_linear
         << ", b_nonlinear=" << b_nonlinear << ", c=" << c << ", d=" << d << endl;
    cout << "Начальная температура: " << y0 << endl << endl;

    // Линейная модель
    vector<double> y_linear = linearModel(a, b_linear, y0, u, timeSteps);
    cout << "Линейная модель:" << endl;
    for (int t = 0; t < timeSteps; t++) {
        cout << "t=" << t << ": y=" << y_linear[t] << endl;
    }

    cout << endl;

    // Нелинейная модель
    vector<double> y_nonlinear = nonlinearModel(a, b_nonlinear, c, d, y0, u, timeSteps);
    cout << "Нелинейная модель:" << endl;
    for (int t = 0; t < timeSteps; t++) {
        cout << "t=" << t << ": y=" << y_nonlinear[t] << endl;
    }

    return 0;
}
