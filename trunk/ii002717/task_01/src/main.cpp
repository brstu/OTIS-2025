#include <iostream>
#include <vector>
#include <cmath>

int main() {
    std::setlocale(LC_ALL, "rus");

    int N;
    std::cout << "Введите число шагов N (N < 100): ";
    std::cin >> N;
    if (N >= 100) {
        std::cout << "Ошибка: выход за границу\n";
        return 0;
    }

    double a;
    double b;
    double c;
    double d;

    std::cout << "Введите константы a, b, c, d: ";
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    std::cin >> d;

    std::vector<double> u(N);
    std::cout << "Введите значения u(t) для t = 0.." << N - 1 << ":\n";
    for (int t = 0; t < N; ++t) {
        std::cout << "u[" << t << "] = ";
        std::cin >> u[t];
    }

    std::vector<double> y_lin(N + 1);
    std::vector<double> y_nl(N + 1);

    std::cout << "Введите начальную температуру y[0]: ";
    std::cin >> y_lin[0];
    y_nl[0] = y_lin[0];

    std::cout << "Введите y[1] для нелинейной модели: ";
    std::cin >> y_nl[1];

    // Линейная модель
    for (int t = 0; t < N; ++t) {
        y_lin[t + 1] = a * y_lin[t] + b * u[t];
    }

    // Нелинейная модель
    for (int t = 1; t < N; ++t) {
        y_nl[t + 1] = a * y_nl[t]
            - b * y_nl[t - 1] * y_nl[t - 1]
                + c * u[t]
                + d * std::sin(u[t - 1]);
    }

    std::cout << "\nРезультаты моделирования:\n";
    std::cout << "t \ty_lin \ty_nl\n";
    for (int t = 0; t <= N; ++t) {
        std::cout << t << "\t" << y_lin[t] << "\t" << y_nl[t] << "\n";
    }

    return 0;
}




