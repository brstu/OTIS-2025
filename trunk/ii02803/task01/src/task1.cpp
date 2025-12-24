#include <iostream>
#include <cmath>

double linear(double y, double u, double a, double b);
double non_linear(double y, double u, double a, double b, double c, double d);

int main()
{
    double warm_input;
    double temp_input;
    std::cout << "Enter u(input warm) and y(input temperature): " << std::endl;
    std::cin >> warm_input >> temp_input;

    double a_val;
    double b_val; 
    double c_val;
    double d_val;
    std::cout << "a,b,c,d: " << std::endl;
    std::cin >> a_val >> b_val >> c_val >> d_val;

    int step_total;
    std::cout << "Number of steps: " << std::endl;
    std::cin >> step_total;

    double lin_y = temp_input;
    double nonlin_y = temp_input;
    for (int i = 0; i < step_total; i++)
    {
        lin_y = linear(lin_y, warm_input, a_val, b_val);
        nonlin_y = non_linear(nonlin_y, warm_input, a_val, b_val, c_val, d_val);

        std::cout << i + 1 << " step of linear model: " << lin_y << ";\n";
        std::cout << i + 1 << " step of non-linear model: " << nonlin_y << ";\n";
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
