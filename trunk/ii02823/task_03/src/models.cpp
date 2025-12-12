#include "models.h"
#include <cmath>

/**
 * @brief Линейная модель объекта управления
 * 
 * Рассчитывает новое значение выходной величины по линейной модели:
 * \f$ y_{k+1} = a \cdot y_k + b \cdot u_k \f$
 * 
 * @param y текущее значение выходной величины
 * @param u управляющее воздействие
 * @param a коэффициент модели
 * @param b коэффициент модели
 * @return новое значение выходной величины
 */
double linear(double y, double u, double a, double b)
{
    return a * y + b * u;
}

/**
 * @brief Нелинейная модель объекта управления
 * 
 * Рассчитывает новое значение выходной величины по нелинейной модели:
 * \f$ y_{k+1} = a \cdot y_k - b \cdot y_{k}^2 + c \cdot u_k + d \cdot \sin(u_k) \f$
 * 
 * @param y текущее значение выходной величины
 * @param y_p предыдущее значения выходной величины
 * @param u управляющее воздействие
 * @param u_p предыдущее управляющее воздействие
 * @param coeffs коэффициенты модели
 * @return новое значение выходной величины
 */
double non_linear(double y, double y_p, double u, double u_p, const NonLinearCoeffs& coeffs)
{
    return coeffs.a * y - coeffs.b * y_p * y_p + coeffs.c * u + coeffs.d * std::sin(u_p);
}