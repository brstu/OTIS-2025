#include <iostream>
#include <cmath>
#include <locale>

double nextLinear(double a, double b, double u, double y)
{
    return a * y + b * u;
}

void simulateLinear(double a, double b, double u, int steps)
{
    std::cout << "Линейная модель" << std::endl;
    double y = 0.0;
    for (int i = 0; i < steps; i++)
    {
        std::cout << "t = " << i << ", y = " << y << std::endl;
        y = nextLinear(a, b, u, y);
    }
}

double nextNonlinear(double a, double b, double c, double d, double u, double uPrev, double y, double yPrev)
{
    return a * y - b * (yPrev * yPrev) + c * u + d * sin(uPrev);
}

void simulateNonlinear(double a, double b, double c, double d, double uInitial, int steps)
{
    std::cout << "Нелинейная модель" << std::endl;
    double y = 0.0;
    double yPrev = 0.0;
    double u = uInitial;
    double uPrev = uInitial;

    for (int i = 0; i < steps; i++)
    {
        std::cout << "t = " << i << ", y = " << y << std::endl;
        double yNext = nextNonlinear(a, b, c, d, u, uPrev, y, yPrev);

        yPrev = y;
        y = yNext;
    }
}

int main()
{
    try {
        std::locale rus_locale("ru_RU.UTF-8");
        std::cout.imbue(rus_locale);
    } catch (const std::runtime_error&) {
        std::cerr << "Russian locale ru_RU.UTF-8 not available, using default locale." << std::endl;
    }
    
    double a1 = 0.3, b1 = 0.3, u1 = 0.9;
    int n1 = 10;
    simulateLinear(a1, b1, u1, n1);

    std::cout << std::endl;

    double a2 = 0.1, b2 = 0.2, c2 = 0.4, d2 = 0.2, u2 = 0.8;
    int n2 = 10;
    simulateNonlinear(a2, b2, c2, d2, u2, n2);

   