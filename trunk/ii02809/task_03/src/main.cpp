#include <iostream>
#include "functions.h"

int main()
{
    double a;
    double b;
    double c;
    double d;
    std::cout << "Enter model parameters a, b, c, d: ";
    std::cin >> a >> b >> c >> d;

    double K;
    double Ti;
    double Td;
    double To;
    std::cout << "Enter PID parameters K, Ti, Td, To: ";
    std::cin >> K >> Ti >> Td >> To;

    double w;
    std::cout << "Enter desired value w: ";
    std::cin >> w;

    int model_type;
    std::cout << "Enter model type (1: linear, 2: nonlinear): ";
    std::cin >> model_type;

    int num_steps;
    std::cout << "Enter number of steps: ";
    std::cin >> num_steps;

    double y = 0.0;

    PID pid(K, Ti, Td, To);

    std::cout << "step,y,u,e" << std::endl;

    for (int k = 0; k < num_steps; ++k)
    {
        double e = w - y;
        double u = pid.compute(e);

        if (model_type == 1)
        {
            y = linear(y, u, a, b);
        }
        else
        {
            y = nonlinear(y, u, a, b, c, d);
        }

        std::cout << k << "," << y << "," << u << "," << e << std::endl;
    }

    return 0;
}
