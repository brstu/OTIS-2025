#include "models.h"

double computeLinear(double state, double signal, double factorA, double factorB) {
    return factorA * state + factorB * signal;
}

double computeNonlinear(double state, double signal,
                        double factorA, double factorB,
                        double factorC, double factorD) {
    double quadraticPart = factorB * state * state;
    double sinusPart = factorD * sin(signal);
    return factorA * state - quadraticPart + factorC * signal + sinusPart;
}
