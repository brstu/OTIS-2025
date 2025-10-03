#include <iostream>
#include <cmath>

int main()
{
	double y;
	double y_prev;
	double y_next;
	double u;
	double a;
	double b;
	double c;
	double d;
	int n;
	std::cout << "Enter y(starting temperature) and u(input warmth at every step) values: ";
	std::cin >> y >> u; 
	std::cout << "Enter a, b, c, d(constants) values: ";
	std::cin >> a >> b >> c >> d;
	std::cout << "Enter number of steps n: ";
	std::cin >> n;
	y_prev = y;
	for (int i = 0; i < n; i++)
	{
		y = a * y + b * u;
		std::cout << "Result of the " << i + 1 << " step of linear model: " << y << '\n';
	}
	y = y_prev;
	y_prev = 0;
	for (int i = 0; i < n; i++)
	{
		std::cout << "Result of the " << i + 1 << " step of non-linear model: " << y << '\n';
		y_next = a * y - b * y_prev * y_prev + c * u + d * sin(u);//u is equal in every step, so there no sense to add u(t-1)
		y_prev = y;
		y = y_next;
	}
	return 0;
}
