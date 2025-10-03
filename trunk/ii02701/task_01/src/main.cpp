#include <iostream>
#include <cmath>

int main()
{
	double y;
	double y_prev;
	double y_next;
	double u;
	double u_prev;
	double a;
	double b;
	double c;
	double d;
	int n;
	std::cout << "Enter y (starting temperature) and u (input warmth at first step) values (space-separated): ";
	std::cin >> y >> u; 
	std::cout << "Enter a, b, c, d (constants) values: ";
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
	u_prev = u;
	for (int i = 0; i < n; i++)
	{
		y_next = a * y - b * y_prev * y_prev + c * u + d * sin(u_prev); // Use previous input value as per specification
		y_prev = y;
		y = y_next;
		std::cout << "Result of the " << i + 1 << " step of non-linear model: " << y << '\n';
		std::cout << "Enter u for the " << i + 1 << " step: ";
		u_prev = u; // Update u_prev to current input value for next iteration (if u changes per step)
		std::cin >> u;
	}
	return 0;
}
