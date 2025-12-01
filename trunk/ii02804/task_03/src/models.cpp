#include "models.h"
#include <cmath>

/**
 * @brief Вычисляет новое состояние линейной модели.
 *
 * Формула:
 * y(k) = a * y(k-1) + b * u(k)
 */
double linear_model(double y_prev, double u, double a, double b) {
    return a * y_prev + b * u;
}


/**
 * @brief Вычисляет новое состояние нелинейной модели.
 *
 * Формула:
 * y(k+1) = a * y(k) - b * y^2(k-1) + c * u(k) + d * sin(u(k-1))
 */
double nonlinear_model(double y, double y_prev, double u, double u_prev, double a, double b, double c, double d){
    return a * y - b * std::pow(y_prev, 2.0) + c * u + d * std::sin(u_prev);
}
