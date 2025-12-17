#include "models.h"

/**
 * @brief Линейная модель
 */
double linear_model(double y_prev, double u, const LinearParams& p) {
    return p.a * y_prev + p.b * u;
}

/**
 * @brief Нелинейная модель
 */
double nonlinear_model(double y, double y_prev, double u, double u_prev, const NonlinearParams& p) {
    return p.a * y - p.b * y_prev * y_prev + p.c * u + p.d * std::sin(u_prev);
}
