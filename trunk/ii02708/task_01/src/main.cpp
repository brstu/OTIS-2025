#include<iostream>
#include<cmath>

int main()
{
	const float a = 0.5f;
	const float b = 0.2f;
	const float c = 0.15f;
	const float d = 0.3f;
	const float u = 1.2f;

	float y0;
	float y1;
	float y2;
	float y_temp;
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