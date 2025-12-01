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
    double w1;                 // заданная температура
    double y;                 // текущая температура
    double y_prev = 0.0;     // y(k-1) для нелинейной модели

    

    double a1;
    double b1;
    double c1 = 0.0;
    double d1 = 0.0;

   

    double K1  = 0.5;
    double T1  = 2.0;
    double Td = 0.3;
    double T0 = 1.0;

    

    validate(model_type, "Choose model (1 = linear, 2 = nonlinear): ");
    validate(y, "Enter input temperature y0: ");
    validate(a1, "Enter constant a: ");
    validate(b1, "Enter constant b: ");

    if (model_type == 2) {
        validate(c1, "Enter constant c (nonlinear coeff): ");
        validate(d1, "Enter constant d (sin coeff): ");
    }

    validate(w1, "Enter target temperature w: ");
    validate(n, "Enter amount of steps n: ");


    PID pid(K1, T1, Td, T0);

    double u = 0.0;
    double u_prev = 0.0;

    std::cout << "\n PID Simulation \n";


    for (int i = 0; i < n; i++) {

        double e = w1 - y;
        u = pid.u_calc(e);

        double y_next;

        if (model_type == 1) {
            //  Линейная модель 
            y_next = linear_model(y, u, a1, b1);
        }
        else {
            //  Нелинейная модель 
            y_next = nonlinear_model(y, y_prev, u, u_prev, a1, b1, c1, d1);
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
