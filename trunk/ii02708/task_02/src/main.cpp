#include <iostream>
#include "linear.h"
#include "nonlinear.h"

int main()
{
    LinearCoeff linearCoeff;
    linearCoeff.a = 0.5;
    linearCoeff.b = 0.2;
    linearCoeff.u = 1.2;
    
    NonLinearCoeff nonlinearCoeff;
    nonlinearCoeff.a = 0.5;
    nonlinearCoeff.b = 0.2;
    nonlinearCoeff.c = 0.15;
    nonlinearCoeff.d = 0.3;
    nonlinearCoeff.u = 1.2;
    
    double y0;
    std::cout << "y1 = ";
    std::cin >> y0;
    
    int n = 10;
    
    std::cout << std::endl << "Linear" << std::endl;
    std::vector<double> linearResults = calculateLinear(linearCoeff, y0, n);
    for (int i = 0; i < n; i++)
    {
        std::cout << "t" << i + 1 << " = " << linearResults[i] << std::endl;
    }
    
    std::cout << std::endl << "Nonlinear:" << std::endl;
    std::vector<double> nonlinearResults = calculateNonlinear(nonlinearCoeff, y0, n);
    for (int i = 0; i < n; i++)
    {
        std::cout << "t" << i + 1 << " = " << nonlinearResults[i] << std::endl;
    }
    
    return 0;
}