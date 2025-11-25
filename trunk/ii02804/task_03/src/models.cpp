#include "models.h"

/**
 * @brief Вычисляет новое состояние линейной модели.
 *
 * Формула:
 * y(k) = a * y(k-1) + b * u(k)
 */
double linear_model(double y_prev, double u, double a, double b) {
    return a * y_prev + b * u;
}
