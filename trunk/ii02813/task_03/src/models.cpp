#include "models.h"
#include <cmath>

/**
 * @brief Линейная модель объекта управления
 * 
 * Рассчитывает новое значение выходной величины по линейной модели:
 * \f$ y_{k+1} = a \cdot y_k + b \cdot u_k \f$
 * 
 * @param y01 текущее значение выходной величины
 * @param u01 управляющее воздействие
 * @param a01 коэффициент модели
 * @param b01 коэффициент модели
 * @return новое значение выходной величины
 */
double linear(double y01, double u01, double a01, double b01)
{
    return a01 * y01 + b01 * u01;
}

/**
 * @brief Нелинейная модель объекта управления
 * 
 * Рассчитывает новое значение выходной величины по нелинейной модели:
 * \f$ y_{k+1} = a \cdot y_k - b \cdot y_{k}^2 + c \cdot u_k + d \cdot \sin(u_k) \f$
 * 
 * @param y01 текущее значение выходной величины
 * @param y01_p предыдущее значения выходной величины
 * @param u01 управляющее воздействие
 * @param u01_p предыдущее управляющее воздействие
 * @param coeffs коэффициенты модели
 * @return новое значение выходной величины
 */
double non_linear(double y01, double y01_p, double u01, double u01_p, const NonLinearCoeffs& coeffs)
{
    return coeffs.a01 * y01 - coeffs.b01 * y01_p * y01_p + coeffs.c01 * u01 + coeffs.d01 * std::sin(u01_p);
}