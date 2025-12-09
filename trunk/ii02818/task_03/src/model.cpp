/**
 * @file    model.cpp
 * @brief   Реализация класса Model
 * @details Содержит реализацию линейной и нелинейной моделей
 * @author  Vladimir
 * @date    2025-12-09
 * @version 1.0
 */

#include "model.h"
#include <cmath>
#include <iostream>

/**
 * @brief Конструктор класса Model
 * @param a_val Коэффициент A
 * @param b_val Коэффициент B
 * @param c_val Коэффициент C
 * @param d_val Коэффициент D
 */
Model::Model(double a_val, double b_val, double c_val, double d_val)
    : a(a_val), b(b_val), c(c_val), d(d_val) {}

/**
 * @brief Инициализация начальных условий модели
 * @param y0 Начальное значение y[k-2]
 * @param y1 Начальное значение y[k-1]
 * @param u0 Начальное значение u[k-2]
 * @param u1 Начальное значение u[k-1]
 */
void Model::init(double y0, double y1, double u0, double u1) {
    y_prev2 = y0;
    y_prev1 = y1;
    u_prev2 = u0;
    u_prev1 = u1;
}

/**
 * @brief Линейная модель объекта управления
 * @param u Текущее управляющее воздействие
 * @return Текущее значение выхода модели
 * 
 * Реализует разностное уравнение:
 * y[k] = a*y[k-1] + b*u[k]
 */
double Model::linearModel(double u) {
    // Обновление истории входных воздействий
    u_prev2 = u_prev1;
    u_prev1 = u;
    
    // Расчет нового значения выхода
    double y = a * y_prev1 + b * u;
    
    // Обновление истории выходных значений
    y_prev2 = y_prev1;
    y_prev1 = y;
    
    return y;
}

/**
 * @brief Нелинейная модель объекта управления
 * @param u Текущее управляющее воздействие
 * @return Текущее значение выхода модели
 * 
 * Реализует разностное уравнение:
 * y[k] = a*y[k-1] - b*y[k-2]*tanh(y[k-2]) + c*u[k] + d*sin(u[k-1])
 */
double Model::nonlinearModel(double u) {
    // Обновление истории входных воздействий
    u_prev2 = u_prev1;
    u_prev1 = u;

    double y2 = y_prev2;
    double smooth_quad = y2 * std::tanh(y2);

    // Расчет нового значения выхода (нелинейная модель)
    double y = a * y_prev1
               - b * smooth_quad
               + c * u
               + d * std::sin(u_prev1);

    // Ограничение выходных значений для предотвращения нестабильности
    if (y > 1000.0) y = 1000.0;
    if (y < -1000.0) y = -1000.0;
    if (std::isnan(y)) y = 0.0;

    // Обновление истории выходных значений
    y_prev2 = y_prev1;
    y_prev1 = y;

    return y;
}