#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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
 * @brief Линейная модель с передачей коэффициентов через структуру.
 */
double linearModel(double y, double u, const LinearParams& p);

/**
 * @brief Нелинейная модель с передачей коэффициентов через структуру.
 */
double nonlinearModel(double y, double y_prev, double u, double u_prev, const NonlinearParams& p);

#endif // FUNCTIONS_H
