#include <iostream>
#include "l.h"
#include "nonl.h"

int main()
{
    linear_cff linears_cff;
    linears_cff.a = 0.5;
    linears_cff.b = 0.2;
    linears_cff.u = 1.2;

    NonLinear_Cff nonlinears_cff;
    nonlinears_cff.a = 0.5;
    nonlinears_cff.b = 0.2;
    nonlinears_cff.c = 0.15;
    nonlinears_cff.d = 0.3;
    nonlinears_cff.u = 1.2;

    double y0;
    std::cout << "y1 = ";
    std::cin >> y0;

    int n = 10;

    std::cout << std::endl << "Linear" << std::endl;
    std::vector<double> linear_results = calculateLinear(linears_cff, y0, n);
    for (int i = 0; i < n; i++)
    {
        std::cout << "t" << i + 1 << " = " << linear_results[i] << std::endl;
    }

    std::cout << std::endl << "Nonlinear:" << std::endl;
    std::vector<double> nonlinear_results = calculateNonlinear(nonlinears_cff, y0, n);
    for (int i = 0; i < n; i++)
    {
        std::cout << "t" << i + 1 << " = " << nonlinear_results[i] << std::endl;
    }

    return 0;
}