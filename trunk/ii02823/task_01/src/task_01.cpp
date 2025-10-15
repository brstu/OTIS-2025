#include <iostream>
#include <cmath>

double linear(double y, double u, double a, double b)
{
    return a * y + b * u;
}

double non_linear(double y, double& y_p, double u, double a, double b, double c, double d)
{
    y_p = y;
    return a * y - b * y_p * y_p + c * u + d * std::sin(u);
}

int main()
{
    double y;
    double y_p;
    double u;
    std::cout << "Enter Yn-1, Y and U values:\n";
    std::cin >> y_p  >> y >> u;
    
    double a;
    double b;
    double c;
    double d;
    std::cout << "Enter A, B, C, D values:\n";
    std::cin >> a >> b >> c >> d;

    int n;
    std::cout << "Enter number of steps N: ";
    std::cin >> n;

    double y1 = y;
    
    double y2 = y;
    double y2_p = y_p;

    for (int i = 0; i < n; i++)
    {
        y1 = linear(y1, u, a, b);
        std::cout << "The " << i << "st step of linear model - " << y1 << std::endl;
    }

    for (int i = 0; i < n; i++)
    {
        y2 = non_linear(y2, y2_p, u, a, b, c, d);
        std::cout << "The " << i << "st step of nonlinear model - " << y2 << std::endl;
    }

    return 0;
}
