#pragma once
#include <cmath>

// Линейная модель
double computeLinear(double state, double signal, double factorA, double factorB);

// Нелинейная модель
double computeNonlinear(double state, double signal,
                        double factorA, double factorB,
                        double factorC, double factorD);
