#include "model.h"

Model::Model(double initial_state, double a_coeff)
    : x(initial_state), a(a_coeff) {}

double Model::update(double u, double dt) {
    // dx/dt = -a * x + u
    double dx = -a * x + u;
    x += dx * dt;
    return x;
}

double Model::getState() const {
    return x;
}
