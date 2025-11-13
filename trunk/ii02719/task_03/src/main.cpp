#include "functions.h"
#include <iostream>
#include <cmath>
#include <vector>

int main()
{
	setlocale(LC_ALL, "Russian");

	const int steps = 30;
	std::vector<double> y;
	y.resize(steps);
	double a = 0.8;
	double b = 0.5;

	std::cout << "Рассчет по линейной модели\n";
	std::cout << "Введите начальную температуру объекта y(0): ";
	std::cin >> y[0];

    linear(a, b, y, steps);

	std::cout << "Нажмите Enter для выхода...";
	std::cin.ignore();
	std::cin.get();
}