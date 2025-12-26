#pragma once
#include <cmath>
#include <vector>

/**
 * @struct NonLinearCoeff
 * @brief Структура для хранения коэффициентов нелинейной модели
 * 
 * Нелинейная модель описывается разностным уравнением:
 * y(t) = a*y(t-1) - b*y(t-2)^2 + c*u + d*sin(u)
 */
struct NonLinearCoeff{
    double a; ///< Коэффициент при y(t-1)
    double b; ///< Коэффициент при квадрате y(t-2)
    double c; ///< Коэффициент при управляющем воздействии u
    double d; ///< Коэффициент при синусе управляющего воздействия sin(u)
    double u; ///< Управляющее воздействие
};

/**
 * @brief Вычисляет значения нелинейной модели на n шагов вперед
 * 
 * Функция реализует расчет нелинейной модели по формуле:
 * y(t) = a*y(t-1) - b*y(t-2)^2 + c*u + d*sin(u)
 * 
 * @param coeff Коэффициенты нелинейной модели
 * @param y0 Начальное значение y(0)
 * @param n Количество шагов расчета
 * @return std::vector<double> Вектор значений y для каждого шага времени
 * 
 * @note Для вычислений используются два предыдущих значения:
 * y0 = y(t-2), y1 = y(t-1) на каждой итерации
 * 
 * @warning Значения в векторе результатов соответствуют моментам времени t=1..n
 * 
 * @example 
 * NonLinearCoeff coeff = {0.5, 0.2, 0.15, 0.3, 1.2};
 * auto results = calculateNonlinear(coeff, 1.0, 10);
 */
std::vector<double> calculateNonlinear(const NonLinearCoeff &coeff, double y0, int n)
{
    std::vector<double> results;
    double y1 = y0;
    double y2 = y0;
    for (int i = 0; i < n; i++)
	{
		y2 = coeff.a * y1 - coeff.b * y0 * y0 + coeff.c * coeff.u + coeff.d * sin(coeff.u);
        results.push_back(y2);
		y0 = y1;
		y1 = y2;
	}
    return results;
}