#include "pid.h"

namespace {

void makeDiscrete(double K, double Ti, double Td, double T,
                  double& q0, double& q1, double& q2)
{
    if (Ti <= 0.0) {
        // Пропорционально-дифференциальный регулятор (без интегральной составляющей)
        q0 = K * (1.0 + Td / T);
        q1 = -K * (1.0 + 2.0 * Td / T);
        q2 = K * (Td / T);
    } else {
        // Полный ПИД-регулятор
        const double a = T / (2.0 * Ti);
        const double b = Td / T;

        q0 = K * (1.0 + a + b);
        q1 = -K * (1.0 - a + 2.0 * b);
        q2 = K * b;
    }
}

} // namespace

PID::PID(double K, double Ti, double Td, double T)
{
    makeDiscrete(K, Ti, Td, T, q0, q1, q2);
}

PID::PID(DiscreteTag, double a, double b, double c, double u0)
    : q0(a), q1(b), q2(c), u_prev(u0)
{
}

void PID::reset(double u0)
{
    u_prev = u0;
    e_prev1 = 0.0;
    e_prev2 = 0.0;
}

double PID::update(double e)
{
    const double u =
        u_prev +
        q0 * e +
        q1 * e_prev1 +
        q2 * e_prev2;

    e_prev2 = e_prev1;
    e_prev1 = e;
    u_prev  = u;

    return u;
}