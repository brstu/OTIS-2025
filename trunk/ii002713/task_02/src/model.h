#ifndef MODULE_H
#define MODULE_H

#include <iostream>
#include <cmath>

// структура параметров нелинейной модели
struct NonlinearParams {
    double a;
    double b;
    double c;
    double d;
};

// линейная модель
double Linear(double a, double b, double u, double y);

// симуляция линейной модели
void simulateLinear(double a, double b, double u, int steps);

// нелинейная модель
double Nonlinear(const NonlinearParams& p, double u, double uPrev, double y, double yPrev);

// симуляция нелинейной модели
void simulateNonlinear(const NonlinearParams& p, double u, int steps);

#endif // MODULE_H