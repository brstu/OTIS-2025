/**
 * @file model.h
 * @brief Простейшая модель объекта (линейная и нелинейная)
 */

#pragma once

struct ModelParams {
    double a;
    double b;
    double c; // используется для нелинейной модели
    double d; // используется для нелинейной модели
};

/**
 * @brief Линейная модель: y_next = a*y_prev + b*u
 */
double plant_linear(double y_prev, double u, const ModelParams& p);

/**
 * @brief Нелинейная модель: y_next = a*y_prev - b*y_prev2^2 + c*u + d*sin(u)
 */
double plant_nonlinear(double y_prev, double y_prev2, double u, const ModelParams& p);
