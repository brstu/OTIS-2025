#pragma once
#include <cmath>
#include <vector>

struct NonLinearCff{    
    double a;
    double b;
    double c;
    double d;
    double u;
};

std::vector<double> calculateNonlinear(const NonLinearCff &coeff, double y0, int n)
{
    std::vector<double> result;
    double y1 = y0;
    double y2 = y0;
    for (int i = 0; i < n; i++)
	{
		y2 = coeff.a * y1 - coeff.b * y0 * y0 + coeff.c * coeff.u + coeff.d * sin(coeff.u);
        result.push_back(y2);
		y0 = y1;
		y1 = y2;
	}
    return result;
}