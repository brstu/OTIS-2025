#include <cmath>
#include "functions.h"

double linear(double y, double u, double a, double b) {
    return a * y + b * u;
}

double nonlinear(double y, double u, double a, double b, double c, double d) {
    return a * y - b * pow(y, 2) + c * u + d * sin(u);
}

PID::PID(double K, double Ti, double Td, double To)
    : q0(K * (1 + Td / To)),
      q1(-K * (1 + 2 * Td / To - To / Ti)),
      q2(K * Td / To),
      e_prev(0.0),
      e_prev2(0.0),
      u_prev(0.0)
{

}

double PID::compute(double e) {
    double delta_u = q0 * e + q1 * e_prev + q2 * e_prev2;
    double u = u_prev + delta_u;

    e_prev2 = e_prev;
    e_prev  = e;
    u_prev  = u;

    return u;
}
