#include "control_object.h"

/**
 * @file control_object.cpp
 * @brief Реализация класса объекта управления.
 */

ControlObject::ControlObject(double K, double T, double xi) : K_obj(K), T_obj(T), xi(xi), y(0.0), dy(0.0) {
}

double ControlObject::update(double u, double dt) {
    double ddy = (-y - 2.0 * xi * T_obj * dy + K_obj * u) / (T_obj * T_obj);
    dy += ddy * dt;
    y += dy * dt;
    return y;
}

double ControlObject::getY() const {
    return y;
}