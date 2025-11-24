/**
 * @file model.h
 * @brief Линейная и нелинейная математическая модель
 */

#pragma once
#include <cmath>

/**
 * @struct ModelParameters
 * @brief Параметры для математичких моделей
 */
struct ModelParameters {
    double a;
    double b; 
    double c;
    double d;
};

/**
 * @brief Линейная модель
 * @param y_current Текуший температура
 * @param u_current Текущий воздействие  
 * @param params Параметры модели
 */
double linearModel(double y_current, double u_current, const ModelParameters& params);

/**
 * @brief Нелиненая модель
 * @param y_current Текуший температура
 * @param y_previous предыдущая температура
 * @param u_current Текущий воздействие
 * @param u_previous предыдущее воздействие
 * @param params Параметры модели
 */
double nonlinearModel(double y_current, double y_previous, double u_current, 
                     double u_previous, const ModelParameters& params);