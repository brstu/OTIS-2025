#include <iostream>
#include <cmath>

int main()
{
    double y, u;
    std::cout << "Enter y and u values:\n";
    std::cin >> y >> u;
    
    double a, b, c, d;
    std::cout << "Enter a, b, c, d values:\n";
    std::cin >> a >> b >> c >> d;

    int n;
    std::cout << "Enter number of steps n: ";
    std::cin >> n;

    double y1 = y, y2 = y;
    for (int i = 0; i < n; i++)
    {
        y1 = a * y1 + b * u;
        y2 = a * y2 - b * y2 * y2 + c * u + d * std::sin(u);
        std::cout << "Result of the " << i + 1 << "st step of linear model: " << y1 << ";\n";
        std::cout << "Result of the " << i + 1 << "st step of non-linear model: " << y2 << ";\n";
    }

    return 0;
}
