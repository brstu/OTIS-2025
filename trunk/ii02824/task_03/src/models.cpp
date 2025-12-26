#include "models.h"
#include <cmath>

double linear(double y, double u, double a1, double b1)
{
    return a1 * y + b1 * u;
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
    return coeffs.a1 * y - coeffs.b1 * y_p * y_p + coeffs.c1 * u + coeffs.d1 * std::sin(u_p);
}