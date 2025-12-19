#pragma once
#include <cmath>
#include <vector>

struct NonLinear_Cff{    
    double a;
    double b;
    double c;
    double d;
    double u;
};

std::vector<double> calculateNonlinear(const NonLinear_Cff &cff, double y0, int n)
{
    std::vector<double> result;
    double y1 = y0;
    double y2 = y0;
    for (int i = 0; i < n; i++)
	{
		y2 = cff.a * y1 - cff.b * y0 * y0 + cff.c * cff.u + cff.d * sin(cff.u);
        result.push_back(y2);
		y0 = y1;
		y1 = y2;
	}
    return result;
}