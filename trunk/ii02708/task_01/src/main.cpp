#include<iostream>
#include<cmath>

int main()
{
	const double a = 0.5;
	const double b = 0.2;
	const double c = 0.15;
	const double d = 0.3;
	const double u = 1.2;

	double y0;
	double y1;
	double y2;
	double y_temp;
	std::cout << "y1 = ";
	std::cin >> y_temp;
	y1 = y_temp;
	y0 = y1;
	int n = 10;
	std::cout << std::endl << "Linear"<<std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << "t" << i + 1 << " = ";
		y2 = a * y1 + b * u;
		std::cout << y2 << std::endl;
		y0 = y1;
		y1 = y2;
	}

	std::cout << std::endl << "Nonlinear:" << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << "t" << i + 1 << " = ";
		y2 = a * y1 - b * y0 * y0 + c * u + d * sin(u);
		std::cout << y2 << std::endl;
		y0 = y1;
		y1 = y2;
	}

}