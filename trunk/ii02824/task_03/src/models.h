#pragma once

/**
 * @brief Линейная модель объекта управления
 * @param y текущее значение выходной величины
 * @param u управляющее воздействие
 * @param a коэффициент модели
 * @param b коэффициент модели
 * @return новое значение выходной величины
 */
double linear(double y, double u, double a1, double b1);

struct NonLinearCoeffs {
    double a1; ///< коэффициент линейной части
    double b1; ///< коэффициент квадратичной нелинейности
    double c1; ///< коэффициент управляющего воздействия
    double d1; ///< коэффициент синусоидальной нелинейности
};

/**
 * @brief Нелинейная модель объекта управления
 * @param y текущее значение выходной величины
 * @param y_p предыдущее значения выходной величины
 * @param u управляющее воздействие
 * @param u_p предыдущее управляющее воздействие
 * @param coeffs коэффициенты модели
 * @return новое значение выходной величины
 */
double non_linear(double y, double y_p, double u, double u_p, const NonLinearCoeffs& coeffs);