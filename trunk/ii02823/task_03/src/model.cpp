#include "model.h"

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