#include <iostream>
#include <cmath>

double linear_step(double y, double u, double a, double b) {
    return a * y + b * u;
}

double nonlinear_step(double y, double y_prev, double u, double u_prev, double a, double b, double c, double d) {
    return a * y - b * y_prev * y_prev + c * u + d * sin(u_prev);
}

int main() {
    double y, y_prev, y_next;
    double u, u_prev;
    double a, b, c, d;
    int steps;

    std::cout << "Введите начальное значение температуры y и начальное тепло u (через пробел): ";
    std::cin >> y >> u;

    std::cout << "Введите коэффициенты a, b, c, d: ";
    std::cin >> a >> b >> c >> d;

    std::cout << "Введите количество шагов моделирования: ";
    std::cin >> steps;

    y_prev = y;
    std::cout << "\n--- Линейная модель ---\n";
    for (int i = 1; i <= steps; ++i) {
        y = linear_step(y, u, a, b);
        std::cout << "Шаг " << i << ": y = " << y << '\n';
    }

    y_prev = 0;
    u_prev = u;
    std::cout << "\n--- Нелинейная модель ---\n";
    for (int i = 1; i <= steps; ++i) {
        y_next = nonlinear_step(y, y_prev, u, u_prev, a, b, c, d);
        y_prev = y;
        y = y_next;

        std::cout << "Шаг " << i << ": y = " << y << '\n';

        u_prev = u;
        std::cout << "Введите значение u для следующего шага: ";
        std::cin >> u;
    }

    return 0;
}
