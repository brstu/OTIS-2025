#include  <iostream>
#include  <cmath>
#include <limits>
#include <string>
#include "functions.h"

template <typename N>
void Number_Check(N& number, const std::string& message) {
	std::cout << message;
	while (!(std::cin >> number)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Input correct number: ";
	}
}

int  main()
{
	std::cout << "Hello, I'm glad to see you :)" << '\n';
	int  steps = 0;
	double c = 0;
	double d = 0;
	double a = 0;
	double b = 0;
	double u = 0;
	double u_prev = 0;
	double y_lin_prev = 0;


	Number_Check(y_lin_prev, "Enter input temperature (y): ");
	Number_Check(u, "Enter input warm (u): ");
	Number_Check(a, "Enter constant a: ");
	Number_Check(b, "Enter constant b: ");
	Number_Check(c, "Enter constant c: ");
	Number_Check(d, "Enter constant d: ");
	Number_Check(steps, "Enter an amount of steps: ");

	double y_nonlin_0 = 0;
	double y_nonlin_1 = y_lin_prev;
	double y_nonlin_2 = 0;


	for (int i = 1; i <= steps; i++)
	{
		y_lin_prev = linear_model(a, b, y_lin_prev, u);

		y_nonlin_2 = a * y_nonlin_1 - b * std::pow(y_nonlin_0, 2) + c * u + d * std::sin(u_prev);

		y_nonlin_0 = y_nonlin_1;

		y_nonlin_1 = y_nonlin_2;

		u_prev = u;
		std::cout << "Step " << i
			<< ", temp of linear function = " << y_lin_prev
			<< ", temp of nonlinear function = " << y_nonlin_2 << std::endl;
	}
	std::cout << "Thanks for using this program! :D" << '\n';
	return  0;
}