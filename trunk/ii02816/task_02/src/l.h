#pragma once
#include <vector>

struct linear_cff{    
    double a;
    double b;
    double u;
};

std::vector<double> calculateLinear(const linear_cff &cff, double y0, int n)
{
    std::vector<double> result;
    double y1 = y0;
    double y2 = y0;
    for (int i = 0; i < n; i++)
	{
		y2 = cff.a * y1 + cff.b * cff.u;
        result.push_back(y2);
		y1 = y2;
	}    
    return result;
}