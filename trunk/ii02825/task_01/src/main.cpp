#include <iostream>
#include <cmath>

double linear(double y, double u, double a, double b);
double non_linear(double y, double u, double a, double b, double c, double d);

int main()
{
    double input_u;
    double input_y;
    std::cout << "Enter u(input warm) and y(input temperature): " << std::endl;
    std::cin >> input_u >> input_y;

    double coeff_a;
    double coeff_b; 
    double coeff_c;
    double coeff_d;
    std::cout << "Enter a,b,c,d(some constants): " << std::endl;
    std::cin >> coeff_a >> coeff_b >> coeff_c >> coeff_d;

    int steps_count;
    std::cout << "Enter the number of steps: " << std::endl;
    std::cin >> steps_count;

    double linear_y = input_y;
    double nonlinear_y = input_y;
    for (int step = 0; step < steps_count; step++)
    {
        linear_y = linear(linear_y, input_u, coeff_a, coeff_b);
        nonlinear_y = non_linear(nonlinear_y, input_u, coeff_a, coeff_b, coeff_c, coeff_d);

        std::cout << "Result of the " << step + 1 << " step of linear model: " << linear_y << ";\n";
        std::cout << "Result of the " << step + 1 << " step of non-linear model: " << nonlinear_y << ";\n";
    }

    return 0;
}

double linear(double y, double u, double a, double b)
{
    return a * y + b * u;
}

double non_linear(double y, double u, double a, double b, double c, double d)
{
    return a * y - b * y * y + c * u + d * std::sin(u);
}
