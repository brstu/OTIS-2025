#include <iostream>
#include <cmath>
const int MAX_STEPS = 101;
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    int N;
    double a, b, c, d;

    cout << "Введите число шагов N (N < 100): ";
    cin >> N;
    if (N >= 100) {
        cout << "Ошибка: выход за границу\n";
        return 1;
    }

    cout << "Введите константы a, b, c, d: ";
    cin >> a >> b >> c >> d;

    double u[100];
    cout << "Введите значения u(t) для t = 0.." << N - 1 << ":\n";
    for (int t = 0; t < N; ++t) {
        cout << "u[" << t << "] = ";
        cin >> u[t];
    }

    double y_lin[MAX_STEPS], y_nl[MAX_STEPS];

    cout << "Введите начальную температуру y[0]: ";
    cin >> y_lin[0];
    y_nl[0] = y_lin[0];

    cout << "Введите y[1] для нелинейной модели: ";
    cin >> y_nl[1];

    // Линейная модель: можно считать для всех t
    for (int t = 0; t < N; ++t) {
        y_lin[t + 1] = a * y_lin[t] + b * u[t];
    }

    // Нелинейная модель: начинаем с t = 1
    for (int t = 1; t < N; ++t) {
        y_nl[t + 1] = a * y_nl[t]
                    - b * y_nl[t - 1] * y_nl[t - 1]
                    + c * u[t]
                    + d * sin(u[t - 1]);
    }

    cout << "\nРезультаты моделирования:\n";
    cout << "t  y_lin  y_nl\n";
    for (int t = 0; t <= N; ++t) {
        cout << t << "  " << y_lin[t] << "  " << y_nl[t] << "\n";
    }

    return 0;
}



