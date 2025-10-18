#include "model.h"

// линейная модель
double Linear(double a, double b, double u, double y) {
    return a * y + b * u;
}

// симуляция линейной модели
void simulateLinear(double a, double b, double u, int steps) {
    std::cout << "Linear model" << std::endl;
    double y = 0.0;
    for (int i = 0; i < steps; ++i) {
        std::cout << "Step " << i << ": " << y << std::endl;
        y = Linear(a, b, u, y);
    }
    std::cout << std::endl;
}

// нелинейная модель
double Nonlinear(const NonlinearParams& p, double u, double uPrev, double y, double yPrev) {
    return p.a * y - p.b * (yPrev * yPrev) + p.c * u + p.d * sin(uPrev);
}

// симуляция нелинейной модели
void simulateNonlinear(const NonlinearParams& p, double u, int steps) {
    std::cout << "Nonlinear model" << std::endl;
    double y = 0.0;
    double yPrev = 0.0;
    double uPrev = 0.0;
    for (int i = 0; i < steps; ++i) {
        std::cout << "Step " << i << ": " << y << std::endl;
        double yNext = Nonlinear(p, u, uPrev, y, yPrev);
        yPrev = y;
        uPrev = u;
        y = yNext;
    }
    std::cout << std::endl;
}