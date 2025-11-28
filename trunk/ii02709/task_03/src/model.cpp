#include "model.h"

Model::Model(double aa, double bb, double t_room, double dtt)
    : a(aa), b(bb), T_room(t_room), dt(dtt), T(t_room) {}

double Model::update(double u)
{
    double dT = -a * (T - T_room) + b * u;
    T += dt * dT;
    return T;
}