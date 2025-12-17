#include <iostream>
#include <cmath>

int main()
{
    double u_current;
    double u_prev;
    double y;
    double a;
    double b;
    double c;
    double d;
    int count_steps;

    std::cout << "Enter initial temperature y: ";
    if (!(std::cin >> y)) {
        std::cerr << "Error: Invalid input for y" << std::endl;
        return 1;
    }

    std::cout << "Enter initial heat u: ";
    if (!(std::cin >> u_current)) {
        std::cerr << "Error: Invalid input for u" << std::endl;
        return 1;
    }

    u_prev = u_current;

    std::cout << "Enter constants a, b, c, d: ";
    if (!(std::cin >> a >> b >> c >> d)) {
        std::cerr << "Error: Invalid input for constants" << std::endl;
        return 1;
    }

    std::cout << "Enter number of steps: ";
    if (!(std::cin >> count_steps) || count_steps <= 0) {
        std::cerr << "Error: Invalid number of steps" << std::endl;
        return 1;
    }

    double y_linear = y;
    double y_nonlinear_prev = y;
    double y_nonlinear = y;

    std::cout << "\nSimulation results:" << std::endl;
    for (int i = 0; i < count_steps; i++)
    {
        double y_linear_next = a * y_linear + b * u_current;
        std::cout << "Step:  " << i + 1 << " linear model" << std::endl;
        std::cout << " y = " << y_linear_next << std::endl;

        u_prev = u_current;
        y_linear = y_linear_next;
    }
    for (int i = 0; i < count_steps; i++)
    {
        double y_nonlinear_next = a * y_nonlinear - b * y_nonlinear_prev * y_nonlinear_prev
            + c * u_current + d * std::sin(u_prev);
        std::cout << "Step: " << i + 1 << " nonlinear model" << std::endl;
        std::cout << " y = " << y_nonlinear_next << std::endl;
        y_nonlinear_prev = y_nonlinear;
        y_nonlinear = y_nonlinear_next;
        u_prev = u_current;
    }

    return 0;
}
