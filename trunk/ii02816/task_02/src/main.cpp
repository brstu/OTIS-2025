#include <iostream>
#include "l.h"
#include "nonl.h"

int main()
{
    LinearCff linearCff;
    linearCff.a = 0.5;
    linearCff.b = 0.2;
    linearCff.u = 1.2;

    NonLinearCff nonlinearCff;
    nonlinearCff.a = 0.5;
    nonlinearCff.b = 0.2;
    nonlinearCff.c = 0.15;
    nonlinearCff.d = 0.3;
    nonlinearCff.u = 1.2;

    double y0;
    std::cout << "y1 = ";
    std::cin >> y0;

    int n = 10;

    std::cout << std::endl << "Linear" << std::endl;
    std::vector<double> linearResults = calculateLinear(linearCff, y0, n);
    for (int i = 0; i < n; i++)
    {
        std::cout << "t" << i + 1 << " = " << linearResults[i] << std::endl;
    }

    std::cout << std::endl << "Nonlinear:" << std::endl;
    std::vector<double> nonlinearResults = calculateNonlinear(nonlinearCff, y0, n);
    for (int i = 0; i < n; i++)
    {
        std::cout << "t" << i + 1 << " = " << nonlinearResults[i] << std::endl;
    }

    return 0;
}