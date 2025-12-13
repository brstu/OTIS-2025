#include "functions.h"
#include <iostream>
#include <cmath>
#include <vector>

/**
 * @brief Главная функция программы.
 *
 * Выполняет расчет по линейной модели температуры объекта.
 * Пользователь вводит начальное значение температуры, после чего вызывается функция linear
 * для моделирования изменения температуры на заданном количестве шагов.
 *
 * @return int Код завершения программы (0 — успешное завершение).
 */
int main()
{
	setlocale(LC_ALL, "Russian");
	/// Количество шагов моделирования
	const int steps = 100;
	/// Вектор значений температуры на каждом шаге
	std::vector<double> y;
	y.resize(steps);
	/// Коэффициент линейной модели (первый параметр)
	double a = 0.8;
	/// Коэффициент линейной модели (второй параметр)
	double b = 0.5;
	double target = 100;

	std::cout << "Calculation using a linear model\n";
	std::cout << "Enter the initial temperature of the object y(0): ";
	std::cin >> y[0];
	std::cout << "Enter the target temperature of the object: ";
	std::cin >> target;

    linear(a, b, y, steps, target);

	std::cout << "Press Enter to exit...";
	std::cin.ignore();
	std::cin.get();
}