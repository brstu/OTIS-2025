#include "functions.h"
#include <iostream>
#include <cmath>

int main()
{
	setlocale(LC_ALL, "Russian");

	const int steps = 10;
	std::vector<double> y;
	y.resize(steps);
	std::vector<double> u;
	u.resize(steps);
	double a;
	double b;
	double c;
	double d;

	std::cout << "Рассчет по линейной модели\n";
	std::cout << "Введите коэффициент a: ";
	std::cin >> a;
	std::cout << "Введите коэффициент b: ";
	std::cin >> b;
	std::cout << "Введите начальную температуру объекта y(0): ";
	std::cin >> y[0];
	std::cout << "Введите начальную температуру объекта u(0): ";
	std::cin >> u[0];

    linear(a, b, y, u, steps);

	std::cout << "Рассчет по нелинейной модели\n";
	std::cout << "Введите коэффициент a: ";
	std::cin >> a;
	std::cout << "Введите коэффициент b: ";
	std::cin >> b;
	std::cout << "Введите коэффициент c: ";
	std::cin >> c;
	std::cout << "Введите коэффициент d: ";
	std::cin >> d;
	std::cout << "Введите начальную температуру объекта y(0): ";
	std::cin >> y[0];
	std::cout << "Введите следующую температуру объекта y(1): ";
	std::cin >> y[1];
	std::cout << "Введите начальную температуру объекта u: ";
	std::cin >> u[0];
	u[1] = u[0] * 0.8; //Коэффициент понижения температуры объекта

	nonLinear(a, b, c, d, y, u, steps);

	std::cout << "Нажмите Enter для выхода...";
	std::cin.ignore();
	std::cin.get();
}