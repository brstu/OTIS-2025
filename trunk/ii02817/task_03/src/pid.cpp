#include "pid.h"
#include <vector>
#include <algorithm>

PIDController::PIDController(double K, double Ti, double Td, double T0)
{
    setParameters(K, Ti, Td, T0);
}

void PIDController::setParameters(double K, double Ti, double Td, double T0)
{
    this->K = K;
    this->Ti = Ti;
    this->Td = Td;
    this->T0 = T0;

    // Вычисление коэффициентов по рекуррентным формулам
    q0 = K * (1.0 + Td / T0);
    q1 = -K * (1.0 + 2.0 * Td / T0 - T0 / Ti);
    q2 = K * Td / T0;
}

void PIDController::setLimits(double u_min, double u_max)
{
    this->u_min = u_min;
    this->u_max = u_max;
}

void PIDController::reset()
{
    u_prev = 0.0;
    e_prev1 = 0.0;
    e_prev2 = 0.0;
}

double PIDController::calculate(double e)
{
    // Вычисление приращения управления
    double delta_u = q0 * e + q1 * e_prev1 + q2 * e_prev2;

    // Вычисление нового управления
    double u = u_prev + delta_u;

    // Ограничение управления
    u = std::max(u_min, std::min(u_max, u));

    // Обновление памяти
    e_prev2 = e_prev1;
    e_prev1 = e;
    u_prev = u;

    return u;
}

std::vector<double> PIDController::getCoefficients() const
{
    return {q0, q1, q2};
}