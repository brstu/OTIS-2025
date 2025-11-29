#pragma once
#include <vector>

/**
	 * @brief Вызывает функцию линейной модели.
	 *
	 * Функция linear должна быть определена в "functions.h" и моделировать изменение температуры.
	 *
	 * @param a Первый коэффициент модели
	 * @param b Второй коэффициент модели
	 * @param y Вектор значений температуры
	 * @param steps Количество шагов моделирования
	 */
void linear(double a, double b, std::vector<double>& y, const int steps);