#include "model.h"
#include <iostream>
#include <cmath>

/**
 * Линейная модель.
 * y_next = a * y + b * u
 */
double Linear(double a, double b, double u, double y) {
    return a * y + b * u;
}

/**
 * Симуляция линейной модели
 */
void simulateLinear(double a, double b, double u, int steps) {
    std::cout << "Linear Model Simulation:" << '\n';
    double y = 0.0;
    for (int i = 0; i < steps; ++i) {
        std::cout << "Step " << i << ": " << y << '\n';
        y = Linear(a, b, u, y);
    }
    std::cout << '\n';
}

/**
 * Нелинейная модель.
 * y_next = a * y - b * yPrev^2 + c * u + d * sin(uPrev)
 */
double Nonlinear(const NonlinearParams& p, double u, double uPrev, double y, double yPrev) {
    return p.a * y - p.b * (yPrev * yPrev) + p.c * u + p.d * std::sin(uPrev);
}

/**
 * Симуляция нелинейной модели
 */
void simulateNonlinear(const NonlinearParams& p, double u, int steps) {
    std::cout << "Nonlinear Model Simulation:" << '\n';
    double y = 0.0;
    double yPrev = 0.0;
    double uPrev = 0.0;
    for (int i = 0; i < steps; ++i) {
        std::cout << "Step " << i << ": " << y << '\n';
        double yNext = Nonlinear(p, u, uPrev, y, yPrev);
        yPrev = y;
        uPrev = u;
        y = yNext;
    }
    std::cout << '\n';
}
