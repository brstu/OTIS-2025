/// @file models.h
/// @brief Линейная и нелинейная модели объекта управления

#ifndef MODELS_H
#define MODELS_H

/**
 * @brief Линейная модель объекта
 * 
 * @param y текущее значение выхода
 * @param u управляющее воздействие
 * @param a коэффициент при y
 * @param b коэффициент при u
 * @return новое значение выхода y
 */
double linear_model(double y, double u, double a, double b);

/**
 * @brief Нелинейная модель объекта
 * 
 * @param y текущее значение выхода
 * @param y_prev предыдущее значение выхода (обновляется внутри)
 * @param u управляющее воздействие
 * @param u_prev предыдущее значение управляющего воздействия (обновляется внутри)
 * @param a линейный коэффициент при y
 * @param b коэффициент нелинейного члена y^2
 * @param c линейный коэффициент при u
 * @param d коэффициент синусного нелинейного члена
 * @return новое значение выхода y
 */
double non_linear_model(double y, double& y_prev, double u, double& u_prev,
                        double a, double b, double c, double d);

#endif // MODELS_H
