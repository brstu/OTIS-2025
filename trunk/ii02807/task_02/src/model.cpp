#include "model.h"

double nextLinear(double a, double b, double u, double y)
{
    return a * y + b * u;
}

void simulateLinear(double a, double b, double u, int steps)
{
    if (steps <= 0) {
        throw std::invalid_argument("Number of steps must be positive");
    }

    std::cout << "Линейная модель" << std::endl;
    double y_val = 0.0;
    for (int i = 0; i < steps; i++)
    {
        std::cout << "t = " << i << ", y = " << y_val << std::endl;
        y_val = nextLinear(a, b, u, y_val);
    }
}

double nextNonlinear(const NonlinearParams& p)
{
    return p.a * p.y - p.b * (p.yPrev * p.yPrev) + p.c * p.u + p.d * sin(p.uPrev);
}

void simulateNonlinear(double a, double b, double c, double d, double u, int steps)
{
    if (steps <= 0) {
        throw std::invalid_argument("Number of steps must be positive");
    }

    std::cout << "Нелинейная модель" << std::endl;

    NonlinearParams p;
    p.a = a;
    p.b = b;
    p.c = c;
    p.d = d;
    p.u = u;
    p.uPrev = 0.0;
    p.y = 0.0;
    p.yPrev = 0.0;

    for (int i = 0; i < steps; i++)
    {
        std::cout << "t = " << i << ", y = " << p.y << std::endl;

        double yNext = nextNonlinear(p);

        p.yPrev = p.y;
        p.y = yNext;
        p.uPrev = p.u;
    }
}