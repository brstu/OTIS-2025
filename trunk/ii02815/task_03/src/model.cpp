/**
 * @file model.cpp
 * @brief Реализация математических моделей
 */

#include "model.h"

/**
 * @brief Реализация линейной математической модели
 *
 * Использует формулу:
 * y_next = a*y_current + b*u_current
 */
double linearModel(double y_current, double u_current, const ModelParameters& params) {
    return params.a * y_current + params.b * u_current;
}

/**
 * @brief Реализация нелинейной математической модели
 * 
 * Использует формулу:
 * y_next = a*y_current - b*y_previous^2 + c*u_current + d*sin(u_previous)
 */
double nonlinearModel(double y_current, double y_previous, double u_current, 
                     double u_previous, const ModelParameters& params) {
    return params.a * y_current - params.b * y_previous * y_previous + 
           params.c * u_current + params.d * sin(u_previous);
}