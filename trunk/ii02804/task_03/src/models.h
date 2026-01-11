#ifndef MODELS_H
#define MODELS_H

#include <cmath>

/**
 * @brief Параметры линейной модели
 */
struct LinearParams {
    double a;
    double b;
};

/**
 * @brief Параметры нелинейной модели
 */
struct NonlinearParams {
    double a;
    double b;
    double c;
    double d;
};

/**
 * @brief Вычисляем новое состояние линейной модели.
 *
 * Формула:
 * y(k) = a * y(k-1) + b * u(k)
 */
double linear_model(double y_prev, double u, const LinearParams& p);

/**
 * @brief Вычисляем новое состояние нелинейной модели.
 *
 * Формула:
 * y(k+1) = a * y(k) - b * y^2(k-1) + c * u(k) + d * sin(u(k-1))
 */
double nonlinear_model(double y, double y_prev, double u, double u_prev, const NonlinearParams& p);

#endif // MODELS_H
