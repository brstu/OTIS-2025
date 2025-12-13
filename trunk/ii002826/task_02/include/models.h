#ifndef MODELS_H
#define MODELS_H

#include <cmath>

struct ModelParams {
    double a;
    double b;
    double c;
    double d;
};

// Линейная модель
inline double linear_model(double y_prev, double u, double a, double b) {
    return a * y_prev + b * u;
}

// Нелинейная модель
inline double nonlinear_model(double y_prev, double y_prev_2, double u, const ModelParams& p) {
    return p.a * y_prev - p.b * std::pow(y_prev_2, 2) + p.c * u + p.d * std::sin(u);
}

#endif