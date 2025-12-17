#pragma once
#include <vector>

struct LinearCoeff{
    double a;
    double b;
    double u;
};

std::vector<double> calculateLinear(LinearCoeff coeff, double y0, int n)
{
    std::vector<double> results;
    double y1 = y0;
    double y2 = y0;
    for (int i = 0; i < n; i++)
	{
		y2 = coeff.a * y1 + coeff.b * coeff.u;
        results.push_back(y2);
		y0 = y1;
		y1 = y2;
	}
    return results;
}