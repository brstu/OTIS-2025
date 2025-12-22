#include "model.h"
#include <cmath>
#include <iostream>

/**
 * @brief Конструктор модели
 */
Model::Model(double a_val, double b_val, double c_val, double d_val)
    : a(a_val), b(b_val), c(c_val), d(d_val),
      y_prev1(0.0), y_prev2(0.0), u_prev1(0.0), u_prev2(0.0) {}

/**
 * @brief Инициализация начальных условий
 */
void Model::init(double y0, double y1, double u0, double u1) {
    y_prev2 = y0;
    y_prev1 = y1;
    u_prev2 = u0;
    u_prev1 = u1;
}

/**
 * @brief Линейная модель объекта
 */
double Model::linearModel(double u) {
    u_prev2 = u_prev1;
    u_prev1 = u;
    
    double y = a * y_prev1 + b * u;
    
    y_prev2 = y_prev1;
    y_prev1 = y;
    
    return y;
}

/**
 * @brief Нелинейная модель объекта
 */
double Model::nonlinearModel(double u) {
    u_prev2 = u_prev1;
    u_prev1 = u;

    double y2 = y_prev2;
    double smooth_quad = y2 * std::tanh(y2);
    
    double y = a * y_prev1
               - b * smooth_quad
               + c * u
               + d * std::sin(u_prev1);

    if (y > 1000.0) y = 1000.0;
    if (y < -1000.0) y = -1000.0;
    if (std::isnan(y)) y = 0.0;

    y_prev2 = y_prev1;
    y_prev1 = y;

    return y;
}