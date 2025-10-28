#include "model.h"
#include <iostream>
#include <cmath>

double nextLinear(double a, double b, double u, double y) {
    return a * y + b * u;
}

void simulateLinear(double a, double b, double u, int steps) {
    std::cout << "Линейная модель" << std::endl;
    double y = 0.0;
    for (int i = 0; i < steps; i++) {
        std::cout << "τ=" << i << ": y=" << y << std::endl;
        y = nextLinear(a, b, u, y);
    }
}

double nextNonlinear(const NonlinearParams& params, double u_prev, double y, double y_prev) {
    return params.a * y - params.b * (y_prev * y_prev) + params.c * u_prev + params.d * std::sin(u_prev);
}

void simulateNonlinear(double a, double b, double c, double d, double u, int steps) {
    std::cout << "Нелинейная модель" << std::endl;
    double y = 0.0;
    double y_prev = 0.0;
    double u_prev = 0.0;
    
    NonlinearParams params{a, b, c, d};
    
    for (int i = 0; i < steps; i++) {
        std::cout << "τ=" << i << ": y=" << y << std::endl;
        double y_next = nextNonlinear(params, u_prev, y, y_prev);
        y_prev = y;
        y = y_next;
        u_prev = u; 
    }
}