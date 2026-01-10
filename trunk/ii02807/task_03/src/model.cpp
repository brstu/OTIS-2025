#include "model.h"

/**
 * @brief Linear system update.
 *
 * Computes the next state of the system:
 * y_next = a * y + b * u
 *
 * @param y current state
 * @param u control signal
 * @param a model coefficient
 * @param b model coefficient
 * @return next state
 */
double linear(double y, double u, double a, double b) {
    return a * y + b * u;
} 
double nonlinear(double a, double b, double c, double d, double u, double y) {
    return a * u + b * y + c * std::sin(y) - d * y * y;
}
