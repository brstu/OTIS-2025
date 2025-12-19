#pragma once
#include <vector>

struct LinearCff{
    double a;
    double b;
    double u;
};

std::vector<double> calculateLinear(const LinearCff &coeff, double y0, int n)
{
    std::vector<double> result;
    double y1 = y0;
    double y2 = y0;
    for (int i = 0; i < n; i++)
	{
		y2 = coeff.a * y1 + coeff.b * coeff.u;
        results.push_back(y2);
		y1 = y2;
	}
    return result;
}