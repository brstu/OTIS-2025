#ifndef PLANT_H
#define PLANT_H

#include <vector>
#include <cmath>

/**
 * @brief Коэффициенты нелинейной модели.
 *
 * y[i] = a*y[i-1] - b*y[i-2]^2 + c*u[i-1] + d*sin(u[i-2])
 */
struct abcd {
    double a{1.0};
    double b{0.0};
    double c{1.0};
    double d{0.0};
};

/**
 * @brief Линейная дискретная модель объекта:
 * y[i] = a*y[i-1] + b*u[i-1]
 *
 * @param steps Количество шагов.
 * @param a Коэффициент обратной связи.
 * @param b Коэффициент передачи управляющего сигнала.
 * @param u Управляющее воздействие (вектор длины >= steps).
 * @param y0 Начальное значение y(0).
 * @param y1 Значение y(1).
 * @return Вектор выходной переменной y.
 */
std::vector<double> linear_func(int steps, double a, double b,
                                const std::vector<double>& u, double y0, double y1);

/**
 * @brief Нелинейная дискретная модель объекта:
 * y[i] = a*y[i-1] - b*y[i-2]^2 + c*u[i-1] + d*sin(u[i-2])
 *
 * @param steps Количество шагов.
 * @param str_fun Структура коэффициентов (a,b,c,d).
 * @param u Управляющее воздействие (вектор длины >= steps).
 * @param y0 Начальное значение y(0).
 * @param y1 Значение y(1).
 * @return Вектор выходной переменной y.
 */
std::vector<double> nonlinear_func(int steps, const abcd& str_fun,
                                   const std::vector<double>& u, double y0, double y1);

#endif
