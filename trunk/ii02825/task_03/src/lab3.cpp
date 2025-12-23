/**
 * @file main.cpp
 * @brief Моделирование работы дискретного PID-регулятора
 * одновременно на линейной и нелинейной модели объекта.
 */

#include <iostream>
#include <cmath>
#include "pid.h"
#include "model.h"

using namespace std;

/**
 * @brief Точка входа в программу.
 *
 * Программа моделирует работу PID-регулятора для двух моделей объекта:
 *  - линейной:
 *      y(k+1) = a*y(k) + b*u(k)
 *
 *  - нелинейной:
 *      y(k+1) = a*y(k) − b*y²(k) + c*u(k) + d*sin(u(k))
 *
 * Выводит на каждом шаге:
 *  - ошибку e
 *  - управляющее воздействие u
 *  - состояние объекта для линейной модели
 *  - состояние объекта для нелинейной модели
 *
 * @return 0 — успешное завершение
 */
int main()
{
    double y0; /**< Начальная температура объекта */
    double a;
    double b; /**< Коэффициенты линейной модели */

    cout << "Enter initial temperature y: ";
    cin >> y0;

    cout << "Enter parameters a and b for linear model: ";
    cin >> a >> b;

    double w; /**< Целевая температура */
    cout << "Enter target temperature w: ";
    cin >> w;

    int steps; /**< Количество шагов моделирования */
    cout << "Enter number of simulation steps: ";
    cin >> steps;

    // Параметры PID-регулятора
    double K = 0.4;
    double T = 3.0;
    double Td = 0.1;
    double T0 = 1.0;

    PID pid(K, T, Td, T0);

    double y_lin = y0; /**< Состояние линейной модели */
    double y_non = y0; /**< Состояние нелинейной модели */

    // Коэффициенты нелинейной модели
    double c = 0.2;
    double d = 0.15;

    cout << "\n=== Simulation started ===\n";
    cout << "Step | e | u | y_linear | y_non_linear\n";

    for (int k = 0; k < steps; k++)
    {
        double e = w - y_lin;      /**< Ошибка управления */
        double u = pid.compute(e); /**< Управляющее воздействие */

        // Модели
        y_lin = linear(y_lin, u, a, b);
        y_non = non_linear(y_non, u, a, b, c, d);

        cout << "Step " << k
             << "  e=" << e
             << "  u=" << u
             << "  y_lin=" << y_lin
             << "  y_non=" << y_non
             << endl;
    }

    return 0;
}
