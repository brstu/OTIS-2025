/**
 * @file main.cpp
 * @brief Консольное приложение моделирования PID-регулятора
 *        для линейной и нелинейной моделей объекта.
 */

#include <iostream>
#include <limits>
#include <string>

#include "pid.h"
#include "models.h"

/**
 * @brief Проверка корректности ввода числового значения.
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

    int model_type;           // 1 - линейная, 2 - нелинейная
    int n;                    // число шагов
    double w;                 // заданная температура
    double y;                 // текущая температура
    double y_prev = 0.0;      // y(k-1) для нелинейной модели

    double K  = 0.5;
    double T  = 2.0;
    double Td = 0.3;
    double T0 = 1.0;

    validate(model_type, "Choose model (1 = linear, 2 = nonlinear): ");
    validate(y, "Enter input temperature y0: ");

    // Коэффициенты для моделей
    LinearParams lp{0.0, 0.0};
    NonlinearParams np{0.0, 0.0, 0.0, 0.0};

    validate(lp.a, "Enter constant a: ");
    validate(lp.b, "Enter constant b: ");

    if (model_type == 2) {
        validate(np.c, "Enter constant c (nonlinear coeff): ");
        validate(np.d, "Enter constant d (sin coeff): ");
        np.a = lp.a;
        np.b = lp.b;
    }

    validate(w, "Enter target temperature w: ");
    validate(n, "Enter amount of steps n: ");

    PID pid(K, T, Td, T0);

    double u = 0.0;
    double u_prev = 0.0;

    std::cout << "\nPID Simulation\n";

    for (int i = 0; i < n; i++) {

        double e = w - y;
        u = pid.u_calc(e);

        double y_next;

        if (model_type == 1) {
            // Линейная модель 
            y_next = linear_model(y, u, lp);
        } else {
            // Нелинейная модель 
            y_next = nonlinear_model(y, y_prev, u, u_prev, np);
        }

        std::cout << "Step " << i + 1
                  << " | e = " << e
                  << " | u = " << u
                  << " | y = " << y_next
                  << std::endl;

        y_prev = y;
        y = y_next;
        u_prev = u;
    }

    return 0;
}
