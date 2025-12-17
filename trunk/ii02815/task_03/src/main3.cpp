/**
 * @file main.cpp
 * @brief главная программа моделирования дискретного PID-регулятора.
 *
 * Программа запрашивает у пользователя параметры модели:
 * - начальную температуру объекта,
 * - коэффициенты модели (a, b, c, d),
 * - целевую температуру,
 * - число шагов моделирования.
 *
 * Затем создаёт PID-регулятор, моделирует поведение объекта
 * с использованием линейной и нелинейной моделей
 * и выводит результаты каждого шага.
 */

#include <iostream>
#include "pid_contr.h"
#include "model.h"

using namespace std;

int main() {
    ModelParameters params;  /**< Параметры математических моделей */
    double y0;               /**< Начальная температура объекта */
    double w;                /**< Целевая температура */
    int steps;               /**< Количество шагов моделирования */

    cout << "Enter initial temperature y: ";
    cin >> y0;

    cout << "Enter model parameters a, b, c, d: ";
    cin >> params.a >> params.b >> params.c >> params.d;

    cout << "Enter target temperature w: ";
    cin >> w;

    cout << "Enter number of simulation steps: ";
    cin >> steps;

    // Параметры PID-регулятора
    double K  = 0.08;  /**< Усиление */
    double T  = 4.0;  /**< Время интегрирования */
    double Td = 1.5;  /**< Время дифференцирования */
    double T0 = 1.0;  /**< Шаг дискретизации */

    cout << "\n=== LINEAR MODEL SIMULATION ===" << endl;
    PID pid_linear(K, T, Td, T0);
    double y_linear = y0;

    cout << "Step\tError\tControl\tOutput" << endl;
    cout << "----\t-----\t-------\t------" << endl;

    for (int k = 0; k < steps; k++) {
        double e = w - y_linear;
        double u = pid_linear.compute(e);
        y_linear = linearModel(y_linear, u, params);

        cout << k << "\t" << e << "\t" << u << "\t" << y_linear << endl;
    }

    cout << "\n=== NONLINEAR MODEL SIMULATION ===" << endl;
    PID pid_nonlinear(K, T, Td, T0);
    double y_nonlinear = y0;
    double y_prev = y0;
    double u_prev = 0.0;

    cout << "Step\tError\tControl\tOutput" << endl;
    cout << "----\t-----\t-------\t------" << endl;

    for (int k = 0; k < steps; k++) {
        double e = w - y_nonlinear;
        double u = pid_nonlinear.compute(e);
        double y_next = nonlinearModel(y_nonlinear, y_prev, u, u_prev, params);

        cout << k << "\t" << e << "\t" << u << "\t" << y_nonlinear << endl;

        y_prev = y_nonlinear;
        y_nonlinear = y_next;
        u_prev = u;
    }

    return 0;
}