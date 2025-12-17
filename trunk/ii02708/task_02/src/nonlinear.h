#pragma once
#include <cmath>
#include <vector>

struct NonLinearCoeff{
    double a;
    double b;
    double c;
    double d;
    double u;
};

std::vector<double> calculateNonlinear(NonLinearCoeff coeff, double y0, int n)
{
    std::vector<double> results;
    double y1 = y0;
    double y2 = y0;
    for (int i = 0; i < n; i++)
	{
		y2 = coeff.a * y1 - coeff.b * y0 * y0 + coeff.c * coeff.u + coeff.d * sin(coeff.u);
        results.push_back(y2);
		y0 = y1;
		y1 = y2;
	}
    return results;
}