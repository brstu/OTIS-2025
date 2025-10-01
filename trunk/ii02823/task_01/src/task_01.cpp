#include <iostream>
#include <cmath>

int main()
{
    double y;
    double u;
    std::cout << "Enter y and u values:\n";
    std::cin >> y >> u;
    
    double a;
    double b;
    double c;
    double d;
    std::cout << "Enter a, b, c, d values:\n";
    std::cin >> a >> b >> c >> d;

    int n;
    std::cout << "Enter number of steps n: ";
    std::cin >> n;

    double y1 = y;
    double y2 = y;
    double y2_prev = y2;
    double u_prev = u;
    for (int i = 0; i < n; i++)
    {
        // If u is meant to change per step, uncomment the next two lines:
        // std::cout << "Enter u value for step " << i + 1 << ": ";
        // std::cin >> u_prev;
        y1 = a * y1 + b * u_prev;
        y2 = a * y2_prev - b * y2_prev * y2_prev + c * u_prev + d * std::sin(u_prev);
        std::cout << "Result of the " << i + 1 << "st step of linear model: " << y1 << ";\n";
        std::cout << "Result of the " << i + 1 << "st step of non-linear model: " << y2 << ";\n";
        y2_prev = y2;
        // If u is meant to change per step, update u_prev here.
    }

    return 0;
}
