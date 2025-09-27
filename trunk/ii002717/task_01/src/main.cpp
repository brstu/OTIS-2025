#include <iostream>
#include <cmath>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    int N;
    double a, b, c, d;

    cout << "Введите число шагов N: ";
    cin >> N;

    cout << "Введите константы a, b, c, d: ";
    cin >> a >> b >> c >> d;

    // Ввод значений u[t]
    double u[100]; // предполагаем, что N <= 100
    cout << "Введите значения u(t) для t = 0.." << N - 1 << ":\n";
    for (int t = 0; t < N; ++t) {
        cout << "u[" << t << "] = ";
        cin >> u[t];
    }

    // Массивы для y_lin и y_nl
    double y_lin[101], y_nl[101];

    cout << "Введите начальную температуру y[0]: ";
    cin >> y_lin[0];
    y_nl[0] = y_lin[0];

    cout << "Введите y[1] для нелинейной модели: ";
    cin >> y_nl[1];

    for (int t = 0; t < N; ++t) {
        y_lin[t + 1] = a * y_lin[t] + b * u[t];

        if (t >= 1) {
            y_nl[t + 1] = a * y_nl[t] - b * y_nl[t - 1] * y_nl[t - 1] + c * u[t] + d * sin(u[t - 1]);
        }
        else {
            y_nl[t + 1] = a * y_nl[t] + c * u[t];
        }
    }
    cout << "\nРезультаты моделирования:\n";
    cout << "t  y_lin  y_nl\n";
    for (int t = 0; t <= N; ++t) {
        cout << t << "  " << y_lin[t] << "  " << y_nl[t] << "\n";
    }
    return 0;
}

