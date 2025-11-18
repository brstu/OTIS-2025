/**
 * @file main.cpp
 * @brief Консольное приложение моделирования PID-регулятора и линейного объекта.
 */

#include <iostream>
#include <limits>
#include <string>
#include "PID.h"
#include "lin_model.h"

 /**
  * @brief Проверка корректности ввода числового значения.
  * @tparam N Числовой тип.
  * @param number Переменная, в которую записывается ввод.
  * @param message Сообщение пользователю.
  */
template <typename N>
void validate(N& number, const std::string& message) {
    std::cout << message;
    while (!(std::cin >> number)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Input correct number: ";
    }
}
int main() {

    double y_prev;
    double y;
    double a;
    double b;
    double w;
    int n;

    double K = 0.5;
    double T = 2.0;
    double Td = 0.3;
    double T0 = 1.0;

    validate(y_prev, "Enter input temperature (y): ");
    validate(a, "Enter constant a (for linear model): ");
    validate(b, "Enter constant b (for linear model): ");
    validate(w, "Enter target temperature (w): ");
    validate(n, "Enter an amount of steps (n): ");

    PID pid(K, T, Td, T0);
    for (int i = 0; i < n; i++) {
        double e = w - y_prev;
        double u = pid.u_calc(e);
        y = linear_model(y_prev, u, a, b);
        y_prev = y;

        std::cout << "Step " << i + 1
            << "  e = " << e << '\t'
            << "  u = " << u << '\t'
            << "  y = " << y << '\n';
    }

    return 0;
}
