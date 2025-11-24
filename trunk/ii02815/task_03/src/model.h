/**
 * @file model.h
 * @brief Линейная и нелинейная математическая модель
 */

#pragma once
#include <cmath>

/**
 * @struct ModelParameters
 * @brief Параметры для математических моделей
 */
struct ModelParameters {
    double a;
    double b; 
    double c;
    double d;
};

/**
 * @brief Линейная модель
 * @param y_current Текущий температура
 * @param u_current Текущее воздействие  
 * @param params Параметры модели
 */
double linearModel(double y_current, double u_current, const ModelParameters& params);

/**
 * @brief Нелинейная модель
 * @param y_current Текущий температура
 * @param y_previous предыдущая температура
 * @param u_current Текущее воздействие
 * @param u_previous предыдущее воздействие
 * @param params Параметры модели
 */
double nonlinearModel(double y_current, double y_previous, double u_current, 
                     double u_previous, const ModelParameters& params);