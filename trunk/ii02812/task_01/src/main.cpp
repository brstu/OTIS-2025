#include  <iostream>
#include  <cmath>

int  main()
{
	double y = 0;
	double u = 0;
	double u_prev = 0;
	double a = 0;
	double b = 0;
	double c = 0;
	double d = 0;

	int  n = 0;

	std::cout << "Enter input temperature (y): ";
	std::cin >> y;
	std::cout << "Enter input warm (u): ";
	std::cin >> u;
	double y0 = 0;
	double y1 = y;
	double y2 = 0;
	std::cout << "Enter constants a, b, c, d: ";
	std::cin >> a >> b >> c >> d;

	std::cout << "Enter an amount of steps (n): ";
	std::cin >> n;

	for (int i = 1; i <= n; i++)
	{
		y = a * y + b * u;
		y2 = a * y1 - b * pow(y0, 2) + c * u + d * sin(u_prev);
		y0 = y1;
		y1 = y2;
		u_prev = u;
		std::cout << "Step " << i
			<< ", temp of linear function = "<< y
			<< ", temp of nonlinear function = " << y2 << std::endl;
	}

	return  0;
}