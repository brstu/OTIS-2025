#pragma once
#include <cmath>

/**
 * @brief Linear system model.
 *
 * Computes the next state of the system:
 * y_next = a * y + b * u
 */
double linear(double y, double u, double a, double b);

/**
 * @brief Nonlinear system model.
 *
 * Computes the next state of the system:
 * y_next = a * y + b * u + c * sin(y) - d * y^2
 */
double nonlinear(double a, double b, double c, double d, double u, double y);
