#include <iostream>
#include <cmath>

double linear(double y, double u, double a, double b);
double non_linear(double y, double u, double a, double b, double c, double d);

int main()
{
    double u;
    double y;
    std::cout << "Enter u(input warm) and y(input temperature): " << std::endl;
    std::cin >> u >> y;

    double a1;
    double b; 
    double c;
    double d;
    std::cout << "a,b,c,d: " << std::endl;
    std::cin >> a1 >> b >> c >> d;

    int count;
    std::cout << "Number of steps: " << std::endl;
    std::cin >> count;

    double yl = y;
    double ynl = y;
    for (int i = 0; i < count; i++)
    {
        yl = linear(yl, u, a1, b);
        ynl = non_linear(ynl, u, a1, b, c, d);

        std::cout <<  i + 1 << " step of linear model: " << yl << ";\n";
        std::cout <<  i + 1 << " step of non-linear model: " << ynl << ";\n";
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