#include <iostream>
#include <cmath>
#include <limits>
#include <string>

template <typename N>
void Number_Check(N& number, const std::string& message) {
	std::cout << message;
	while (!(std::cin >> number)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Input correct number: ";
	}
}

int main()
{
	double y_lin_prev = 0;
	double y_lin_next = 0;
	double u = 0;
	double u_prev = 0;
	double a = 0;
	double b = 0;
	double c = 0;
	double d = 0;

	int n = 0;

	Number_Check(y_lin_prev, "Enter input temperature (y): ");
	Number_Check(u, "Enter input warmth (u): ");
	double y_nonlin_0 = 0;
	double y_nonlin_1 = y_lin_prev;
	double y_nonlin_2 = 0;
	Number_Check(a, "Enter constant a: ");
	Number_Check(b, "Enter constant b: ");
	Number_Check(c, "Enter constant c: ");
	Number_Check(d, "Enter constant d: ");
	Number_Check(n, "Enter an amount of steps (n): ");

	for (int i = 1; i <= n; i++)
	{
		y_lin_next = a * y_lin_prev + b * u;
		y_lin_prev = y_lin_next;
		y_nonlin_2 = a * y_nonlin_1 - b * (y_nonlin_0 * y_nonlin_0) + c * u + d * sin(u_prev);
		y_nonlin_0 = y_nonlin_1;
		y_nonlin_1 = y_nonlin_2;
		u_prev = u;
		std::cout << "Step " << i
			<< ", temp of linear function = " << y_lin_next
			<< ", temp of nonlinear function = " << y_nonlin_2 << std::endl;
	}

	return 0;
}
