#include <iostream>
#include <cmath>

// параметры нелинейной модели
struct NonlinearParams {
    double a;
    double b;
    double c;
    double d;
};

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
    return p.a * y - p.b * (yPrev * yPrev) + p.c * u + p.d * std::sin(uPrev);
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

int main() {
    // параметры линейной модели
    double a1 = 0.1;
    double b1 = 0.3;
    double u1 = 0.5;
    int n1 = 10;

    simulateLinear(a1, b1, u1, n1);

    // параметры нелинейной модели
    NonlinearParams p{0.7, 0.9, 0.11, 0.13};
    double u2 = 0.15;
    int n2 = 10;

    simulateNonlinear(p, u2, n2);

    return 0;
}