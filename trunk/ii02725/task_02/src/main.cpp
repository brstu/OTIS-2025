#include <iostream>
#include <vector>
#include <locale>
#include "module.h"

int main()
{
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int N{};
    std::cout << "Введите число шагов N (N < 100): ";
    std::cin >> N;

    if (N < 0 || N >= 100)
    {
        std::cout << "Ошибка: N должно быть в диапазоне 0 <= N < 100\n";
        return 1;
    }

    double a{};
    double b{};
    double c{};
    double d{};
    std::cout << "Введите константы a, b, c, d через пробел: ";
    std::cin >> a >> b >> c >> d;

    std::vector<double> u(N);
    for (int t = 0; t < N; ++t)
    {
        std::cout << "u[" << t << "] = ";
        std::cin >> u[t];
    }

    std::vector<double> yLin(N + 1);
    std::vector<double> yNon(N + 1);

    std::cout << "Введите начальную температуру y[0]: ";
    std::cin >> yLin[0];
    yNon[0] = yLin[0];

    if (N > 1)
    {
        std::cout << "Введите y[1] для нелинейной модели: ";
        std::cin >> yNon[1];
    }

    calculate_linear_model(N, a, b, u, yLin);

    if (N > 1)
        calculate_nonlinear_model(N, a, b, c, d, u, yNon);

    std::cout << "\nРезультаты:\n";
    std::cout << "t\ty_lin\ty_nl\n";
    for (int t = 0; t <= N; ++t)
        std::cout << t << "\t" << yLin[t] << "\t" << yNon[t] << "\n";

    return 0;
}